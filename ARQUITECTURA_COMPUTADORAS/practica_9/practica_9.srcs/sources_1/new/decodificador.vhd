library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity deco is
  Port (
    A: in STD_LOGIC_VECTOR(3 downto 0);
    B: out STD_LOGIC_VECTOR(6 downto 0)
  );
end deco;

architecture arq_deco of deco is
begin
process (A)
begin
    case A is
        when "0000" => B <= "0000001"; -- "0"     
        when "0001" => B <= "1001111"; -- "1" 
        when "0010" => B <= "0010010"; -- "2" 
        when "0011" => B <= "0000110"; -- "3" 
        when "0100" => B <= "1001100"; -- "4" 
        when "0101" => B <= "0100100"; -- "5" 
        when "0110" => B <= "0100000"; -- "6" 
        when "0111" => B <= "0001111"; -- "7" 
        when "1000" => B <= "0000000"; -- "8"     
        when "1001" => B <= "0000100"; -- "9"
        when others => B <= "1111110"; 
    end case;
end process;
end arq_deco;
