library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity internal is
  Port (
    clr,clk,L,E,D: in STD_LOGIC;
    Q: out STD_LOGIC
  );
end internal;

architecture arq_internal of internal is
begin
process (clk)
begin
    if (clr = '1') then
        Q <= '0';
    elsif (rising_edge(clk)) then
        if (L = '0') and (E = '1') then
            Q <= Q or 1;
        elsif (L = '1') and (E = '0') then
        elsif (L = '0') and (E = '0') then
        
        end if;
    end if;
end process;
end arq_internal;
