#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# 帧捕获: 先复位MCU, 再打开COM2持续监听duration秒, 每收到一行实时写盘并flush(中断不丢数据)。
# 用法: python capture_frame.py [--port COM2] [--duration 300] [--raw frame_capture2.txt] [--no-reset]
import argparse
import subprocess
import time

import serial

PROGRAMMER = r"C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"


def reset_mcu():
    subprocess.run([PROGRAMMER, "-c", "port=SWD", "--rst"],
                   check=True, capture_output=True, timeout=60)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default="COM2")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--duration", type=float, default=300.0)
    ap.add_argument("--raw", default="host_diag/frame_capture2.txt")
    ap.add_argument("--no-reset", action="store_true")
    args = ap.parse_args()

    # 先清空旧文件, 保证本次从头开始
    open(args.raw, "wb").close()

    ser = serial.Serial(args.port, args.baud, timeout=0.2)
    ser.reset_input_buffer()
    if not args.no_reset:
        print("[host] resetting MCU ...", flush=True)
        reset_mcu()
    print(f"[host] listening on {args.port} for {args.duration}s, streaming to {args.raw} ...", flush=True)

    total = 0
    deadline = time.time() + args.duration
    with open(args.raw, "wb") as f:
        while time.time() < deadline:
            data = ser.readline()
            if data:
                f.write(data)
                f.flush()
                total += 1
    ser.close()
    print(f"[host] done, total lines: {total}", flush=True)


if __name__ == "__main__":
    main()
