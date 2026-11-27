#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# 主机侧诊断闭环工具：复位设备 -> 自动读取 @DIAG 快照 -> 解析 key=value -> 健康判定 -> 保存 JSON。
# 用法:
#   python read_diag.py                      # 复位并捕获开机 @DIAG
#   python read_diag.py --no-reset           # 不复位，直接监听(等待设备输出 @DIAG)
#   python read_diag.py --json diag.json     # 另存 JSON
import argparse
import json
import re
import subprocess
import sys
import time

import serial

PROGRAMMER = r"C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"
DIAG_LINE = re.compile(r"^@DIAG\s+(\w+)=(.+?)\s*$")

# 期望值(与固件结构/配置一致)，用于自动健康判定
EXPECTED = {
    "patBytes": 24,
    "recBytes": 28,
    "patBodyOffset": 2,
    "recMagicOffset": 7,
    "pvdBlocked": 0,
    "deviceIdStatus": 0,
}


def reset_mcu():
    subprocess.run([PROGRAMMER, "-c", "port=SWD", "--rst"],
                   check=True, capture_output=True, timeout=60)


def capture(port, baud, duration, do_reset):
    ser = serial.Serial(port, baud, timeout=0.2)
    ser.reset_input_buffer()
    if do_reset:
        print(f"[host] reset MCU, capturing @DIAG on {port} ...")
        reset_mcu()
    else:
        print(f"[host] listening on {port}, waiting for @DIAG ...")

    snapshots, current, in_snap = [], None, False
    deadline = time.time() + duration
    while time.time() < deadline:
        line = ser.readline().decode("utf-8", errors="replace").strip()
        if not line:
            if not do_reset and snapshots:
                break
            continue
        if line == "@DIAG BEGIN":
            current, in_snap = {}, True
            continue
        if line == "@DIAG END":
            if in_snap and current is not None:
                snapshots.append(current)
            current, in_snap = None, False
            if do_reset:
                break
            continue
        m = DIAG_LINE.match(line)
        if in_snap and m:
            key, val = m.group(1), m.group(2)
            current[key] = int(val) if re.fullmatch(r"-?\d+", val) else val
    ser.close()
    return snapshots


def judge(snap):
    problems = []
    for key, exp in EXPECTED.items():
        if key in snap and snap[key] != exp:
            problems.append(f"{key}: expected {exp}, got {snap[key]}")
    if "recordCount" in snap and "capacity" in snap and snap["recordCount"] > snap["capacity"]:
        problems.append("recordCount exceeds capacity")
    if "freeBytes" in snap and "regSize" in snap and snap["freeBytes"] > snap["regSize"]:
        problems.append("freeBytes exceeds region size")
    return problems


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default="COM2")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--duration", type=float, default=20.0)
    ap.add_argument("--no-reset", action="store_true")
    ap.add_argument("--json", default="")
    args = ap.parse_args()

    snapshots = capture(args.port, args.baud, args.duration, not args.no_reset)
    if not snapshots:
        print("[host] FAIL: no @DIAG snapshot captured")
        sys.exit(2)

    all_problems = []
    for i, snap in enumerate(snapshots):
        print(f"\n===== @DIAG snapshot {i + 1} =====")
        for key in sorted(snap):
            print(f"  {key:15s} = {snap[key]}")
        problems = judge(snap)
        all_problems.extend(problems)
        if problems:
            print("  HEALTH: FAIL")
            for p in problems:
                print(f"    - {p}")
        else:
            print("  HEALTH: PASS")

    if args.json:
        with open(args.json, "w", encoding="utf-8") as f:
            json.dump(snapshots, f, indent=2)
        print(f"\n[host] JSON saved: {args.json}")

    sys.exit(1 if all_problems else 0)


if __name__ == "__main__":
    main()
