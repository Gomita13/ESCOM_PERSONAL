library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_UC is
end tb_UC;

architecture Behavioral of tb_UC is
component UC is
    Port ( a0,z,ini,clk,clr : in  STD_LOGIC;
           la,lb,ea,eb,ec : out  STD_LOGIC	
			  );
end component;
signal clk,clr,la,lb,ea,eb,ec: std_logic;
signal ini,z,a0: std_logic := '0';

begin
    instanciaUC: UC port map (
        clk =>clk,
        clr => clr,
        ini => ini,
        z => z,
        a0 => a0, 
        la => la,
        lb => lb,
        ea => ea,
        eb => eb,
        ec => ec
    );
    pro_clk: process
    begin
        clk <= '0';
        wait for 5 ns;
        clk <= '1';
        wait for 5 ns;
    end process;

    process_UC: process     
    begin
        clr <= '1';
        wait for 30 ns;
        clr <= '0';
        wait for 60 ns;
        ini <= '1';
        wait for 10 ns;
        ini <= '0';
        wait for 50 ns;
        a0 <= '1';
        wait for 10 ns;
        a0 <= '0';
        wait for 20 ns;
        a0 <= '1';
        wait for 10 ns;
        a0 <= '0';
        wait for 120 ns;
        z <= '1';
        wait;        
    end process;
end Behavioral;
    