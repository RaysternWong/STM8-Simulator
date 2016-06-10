REM       COMMAND FILE BUILT BY IDEA 
REM       Fri Jun 10 16:08:57 2016
REM
castm8 -l -i"C:\Program Files\COSMIC\CXSTM8_EVAL\HSTM8" "crts.s"
castm8 -l -i"C:\Program Files\COSMIC\CXSTM8_EVAL\HSTM8" "interrupt.s"
cxstm8 -v -l +debug +modsl -wa1050314 -wb1224 -i"C:\Program Files\COSMIC\CXSTM8_EVAL\HSTM8" "vector.c" "main.c"
clnk -o "C:\Users\D203C-01\Desktop\STM8-Simulator\STM8 Simulator (Cosmic)\main.sm8" -m "C:\Users\D203C-01\Desktop\STM8-Simulator\STM8 Simulator (Cosmic)\main.map" "C:\Users\D203C-01\Desktop\STM8-Simulator\STM8 Simulator (Cosmic)\main.lkf"
chex -fm -o "acia.s19" "C:\Users\D203C-01\Desktop\STM8-Simulator\STM8 Simulator (Cosmic)\main.sm8"
clabs "C:\Users\D203C-01\Desktop\STM8-Simulator\STM8 Simulator (Cosmic)\main.sm8"
