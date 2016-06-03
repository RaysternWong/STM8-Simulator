REM       COMMAND FILE BUILT BY IDEA 
REM       Fri Jun 03 16:50:23 2016
REM
clnk -o "acia.sm8" -m "acia.map" "acia.lkf"
chex -fm -o "acia.s19" "acia.sm8"
clabs "acia.sm8"
