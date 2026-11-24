#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# 主机侧诊断工具：打开 ST-Link VCP，复位目标 MCU，捕获开机串口日志。
# 用法: python capture_boot.py [--port COM2] [--duration 8] [--raw out.txt]
import argparse
import subprocess
import sys
import time

import serial

PROGRAMMER = r"C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"


def reset_mcu():
    # 软件复位并让 MCU 重新运行，产生完整开机日志
    subprocess.run(
        [PROGRAMMER, "-c", "port=SWD", "--rst"],
        check=True,
        capture_output=True,
        timeout=60,
    )


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default="COM2")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--duration", type=float, default=8.0)
    ap.add_argument("--raw", default="")
    args = ap.parse_args()

    ser = serial.Serial(args.port, args.baud, timeout=0.2)
    ser.reset_input_buffer()
    time.sleep(0.2)

    print(f"[host] reset MCU via SWD, capturing {args.duration}s on {args.port} ...")
    reset_mcu()

    chunks = []
    deadline = time.time() + args.duration
    while time.time() < deadline:
        data = ser.read(4096)
        if data:
            text = data.decode("utf-8", errors="replace")
            chunks.append(data)
            sys.stdout.write(text)
            sys.stdout.flush()
    ser.close()

    raw = b"".join(chunks)
    if args.raw:
        with open(args.raw, "wb") as f:
            f.write(raw)
        print(f"\n[host] raw log saved: {args.raw} ({len(raw)} bytes)")
    print(f"[host] done, received {len(raw)} bytes")


if __name__ == "__main__":
    main()
