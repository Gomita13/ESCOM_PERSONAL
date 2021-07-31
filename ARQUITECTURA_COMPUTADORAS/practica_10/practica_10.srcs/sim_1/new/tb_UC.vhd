library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_UC is
end tb_UC;

architecture arq_tb_UC of tb_UC is
component UC is 
	Port(
		TIPOR,BEQI,BNEI,BLTI,BLETI,BGTI,BGETI,NA,EQ,NE,LT,LE,GT,GE,CLR,CLK: in STD_LOGIC;
		SDOPC,SM: out STD_LOGIC
	);
end component;
signal sTIPOR,sBEQI,sBNEI,sBLTI,sBLETI,sBGTI,sBGETI,sNA,sEQ,sNE,sLT,sLE,sGT,sGE,sCLR,sCLK,sSDOPC,sSM: STD_LOGIC;
begin
instancia: UC port map(
    TIPOR => sTIPOR,
    BEQI => sBEQI,
    BNEI => sBNEI,
    BLTI => sBLTI,
    BLETI => sBLETI,
    BGTI => sBGTI,
    BGETI => sBGETI,
    NA => sNA,
    EQ => sEQ,
    NE => sNE,
    LT => sLT,
    LE => sLE,
    GT => sGT,
    GE => sGE,
    CLR => sCLR,
    CLK => sCLK,
    SDOPC => sSDOPC,
    SM => sSM
);

reloj: process
begin
    sCLK <= '0';
    wait for 5 ns;
    sCLK <= '1';
    wait for 5 ns;
end process;

process
begin 
    sCLR <= '1';
    wait for 1 ns;
    sCLR <= '0';
    sTIPOR <= '0';
    sBEQI <= '0';
    sBNEI <= '0';
    sBLTI <= '0';
    sBLETI <= '0';
    sBGTI <= '0';
    sBGETI <= '0';
    sNA <= '0';
    sEQ <= '0';
    sNE <= '0';
    sLT <= '0';
    sLE <= '0';
    sGT <= '0';
    sGE <= '0';
    wait for 20 ns;
    sBEQI <= '1';
    sNA <= '1';
    wait for 20 ns;
    sNA <= '0';
    sEQ <= '1';
    wait for 20 ns;
    sBEQI <= '0';
    sTIPOR <= '1';
    wait for 20 ns;
end process;

end arq_tb_UC;
