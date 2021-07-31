library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity contador is
  Port (
    LB, EB, CLR, CLK: in STD_LOGIC;
    QB: out STD_LOGIC_VECTOR(3 downto 0)    
  );
end contador;

architecture arq_contador of contador is
signal sQB: INTEGER range 0 to 9;
signal DB: INTEGER := 0;
begin
process (CLR, CLK)
begin
    if(CLR='1') then
            sQB<=0;
        elsif (rising_edge(CLK)) then
            if (lb='0' and eb='0') then
                sQB <= sQB;
            elsif (lb='1' and eb='0') then
                sQB <= DB;
            elsif (lb='0' and eb='1') then
                sQB <= sQB + 1;
            end if;       
        end if;
        QB <= conv_std_logic_vector(sQB,QB'length);
end process;
end arq_contador;
