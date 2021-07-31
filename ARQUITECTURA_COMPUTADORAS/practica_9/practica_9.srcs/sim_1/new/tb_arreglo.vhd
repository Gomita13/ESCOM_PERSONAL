library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_arreglo is
end tb_arreglo;

architecture arq_tb_arreglo of tb_arreglo is
component arreglo is
  Port (
    DA: in STD_LOGIC_VECTOR(8 downto 0);
    LA,EA,CLR,CLK: in STD_LOGIC;
    QA: out STD_LOGIC_VECTOR(8 downto 0)
  );
end component;
signal siLA, sEA, sCLR, sCLK: STD_LOGIC := '0';
signal sDA, sQA: STD_LOGIC_VECTOR(8 downto 0);
begin
    instancia: arreglo port map(
        DA => sDA,
        LA => siLA,
        EA => sEA,
        CLR => sCLR,
        CLK => sCLK,
        QA => sQA
    );
    
    rejol: process
    begin
        sCLK <= '0';
        wait for 5 ns;
        sCLK <= '1';
        wait for 5 ns;  
    end process;
    
    funcionamiento: process
    begin
        sCLR <= '1';
        wait for 15 ns;
        siLA <= '1';
        sDA <= "010101010";
        sCLR <= '0';
        sEA <= '0';
        wait for 15 ns;
        siLA <= '0';
        sEA <= '1';
        wait for 15 ns;
        wait for 15 ns;
        siLA <= '0';
        sEA <= '1';
        wait for 15 ns;
        wait for 15 ns;
        siLA <= '0';
        sEA <= '1';
        wait for 15 ns;            
    end process;
    
end arq_tb_arreglo;