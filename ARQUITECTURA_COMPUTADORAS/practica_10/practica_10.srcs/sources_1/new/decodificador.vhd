library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decod is
  Port (
        opCode: in STD_LOGIC_VECTOR(4 downto 0);
        TIPOR,BEQI,BNEQI,BLTI,BLETI,BGTI,BGETI: out STD_LOGIC
  );
end decod;

architecture arq_decod of decod is
begin
     TIPOR <= '1' when opCode = "00000" else '0';
     BEQI <= '1' when opCode = "01101" else '0';
     BNEQI <= '1' when opCode = "01110" else '0';
     BLTI <= '1' when opCode = "01111" else '0';
     BLETI <= '1' when opCode = "10000" else '0';
     BGTI <= '1' when opCode = "10001" else '0';
     BGETI <= '1' when opCode = "10010" else '0';
end arq_decod;
