del ld_mcu.bin
rem --bincombined is required: the image has two load regions (LR_IROM1 + LR_VER).
rem Using --bin instead would create a bootload.bin directory with one file per region.
C:\Keil_v5\ARM\ARMCC\bin\fromelf   --bincombined --output   .\bootload.bin   .\targetBoard_G5_TRI_A1_20260915\targetBoard_G5_TRI_A1_20260915.axf
