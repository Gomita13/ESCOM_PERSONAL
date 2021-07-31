library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity nivel is
  Port (
    CLR, CLK: in STD_LOGIC;
    NA: out STD_LOGIC
  );
end nivel;

architecture arq_nivel of nivel is
signal pclk, nclk: STD_LOGIC := '0';
begin
    ppclk: process (clr,clk)
    begin
        if(clr = '1') then
            pclk <= '0';
        elsif (rising_edge(clk)) then
            pclk <= not pclk;
        end if;
    end process;
    
   pnclk: process (clr,clk)
   begin
        if(clr = '1') then
            nclk <= '0';
        elsif (falling_edge(clk)) then
            nclk <= not nclk;
        end if;
   end process;
    
   NA <= nclk xor pclk;
end arq_nivel;
