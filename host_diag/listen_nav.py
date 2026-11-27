#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# 持续监听 COM(不复位)，打印带时间戳的串口输出，重点标记 @NAV 导航诊断，用于手动复现页面跳转问题。
# 用法: python listen_nav.py [--port COM2] [--duration 180] [--raw out.txt]
import argparse
import time

import serial


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", default="COM2")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--duration", type=float, default=180.0)
    ap.add_argument("--raw", default="")
    args = ap.parse_args()

    ser = serial.Serial(args.port, args.baud, timeout=0.2)
    ser.reset_input_buffer()
    print(f"[host] listening on {args.port} for {args.duration}s (no reset) ...")
    chunks = []
    deadline = time.time() + args.duration
    while time.time() < deadline:
        line = ser.readline()
        if not line:
            continue
        chunks.append(line)
        text = line.decode("utf-8", errors="replace").rstrip()
        mark = ">> " if "@NAV" in text else "   "
        print(f"{mark}{time.strftime('%H:%M:%S')} {text}")
    ser.close()
    if args.raw:
        with open(args.raw, "wb") as f:
            f.write(b"".join(chunks))
        print(f"[host] raw saved: {args.raw}")


if __name__ == "__main__":
    main()
