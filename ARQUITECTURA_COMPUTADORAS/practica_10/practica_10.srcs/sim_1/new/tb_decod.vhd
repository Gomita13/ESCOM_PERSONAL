library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_decod is
end tb_decod;

architecture arq_tb_decod of tb_decod is
component decod is
  Port (
        opCode: in STD_LOGIC_VECTOR(4 downto 0);
        TIPOR,BEQI,BNEI,BLTI,BLETI,BGTI,BGETI: out STD_LOGIC
  );
end component;
signal sopCode: STD_LOGIC_VECTOR(4 downto 0);
signal sTIPOR,sBEQI,sBNEI,sBLTI,sBLETI,sBGTI,sBGETI: STD_LOGIC;
begin

instancia: decod port map(
    opCode => sopCode,
    TIPOR => sTIPOR,
    BEQI => sBEQI,
    BNEI => sBNEI,
    BLTI => sBLTI,
    BLETI => sBLETI,
    BGTI => sBGTI,
    BGETI => sBGETI
);

process
begin
    sopCode <= "00000";
    wait for 1 ns;
    sopCode <= "00001";
    wait for 1 ns;
    sopCode <= "01101";
    wait for 1 ns;
end process;
end arq_tb_decod;
