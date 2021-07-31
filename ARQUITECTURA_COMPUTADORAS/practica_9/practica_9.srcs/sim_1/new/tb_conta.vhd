library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_conta is
end tb_conta;

architecture arq_tb_conta of tb_conta is
component contador is
  Port (
    LB, EB, CLR, CLK: in STD_LOGIC;
    QB: out STD_LOGIC_VECTOR(3 downto 0)    
  );
end component;
signal sLB, sEB, sCLR, sCLK: STD_LOGIC;
signal sQB: STD_LOGIC_VECTOR(3 downto 0);
begin
    
    instancia: contador port map(
        lb => sLB,
        eb => sEB,
        clr => sCLR,
        clk => sCLK,
        qb => sQB
    );
    
    reloj: process
    begin
        sCLK <= '0';
        wait for 5 ns;
        sCLK <= '1';
        wait for 5 ns;
    end process;
    
    funcoinamiento: process
    begin
        sCLR <= '1';
        wait for 10 ns;
        sCLR <= '0';
        sLB <= '1';
        sEB <= '0';
        wait for 10 ns;
        sEB <= '1';
        sLB <= '0';
        wait for 10 ns;
        sEB <= '0';
        wait for 10 ns;
        sEB <= '1';
        wait for 10 ns;
        sEB <= '0';
        wait for 10 ns;
        sEB <= '1';
        wait for 10 ns;
        sEB <= '0';
        wait for 10 ns;
        sEB <= '1';
        wait for 10 ns;
        sEB <= '0';
        wait for 10 ns;
        sEB <= '1';
        wait for 10 ns;
        sEB <= '0';
        wait for 10 ns;
    end process;
end arq_tb_conta;
