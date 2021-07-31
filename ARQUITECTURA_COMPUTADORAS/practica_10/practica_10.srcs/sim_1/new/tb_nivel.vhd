library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_nivel is
end tb_nivel;

architecture arq_tb_nivel of tb_nivel is
component nivel is
  Port (
    CLR, CLK: in STD_LOGIC;
    NA: out STD_LOGIC
  );
end component;
signal sCLR, sCLK, sNA: STD_LOGIC;
begin

instancia: nivel port map(
    CLR => sCLR,
    CLK => sCLK,
    NA => sNA    
);

clock: process
begin
    sCLK <= '0';
    wait for 10 ns;
    sCLK <= '1';
    wait for 10 ns;
end process;

process
begin
    sCLR <= '1';
    wait for 2 ns;
    sCLR <= '0';
    wait;
end process;

end arq_tb_nivel;
