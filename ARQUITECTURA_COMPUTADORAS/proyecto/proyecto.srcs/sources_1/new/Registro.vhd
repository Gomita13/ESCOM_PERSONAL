library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Registro is
    Port ( d : in STD_LOGIC_VECTOR (3 downto 0);
           clr,clk,LF : in STD_LOGIC;
           q : out STD_LOGIC_VECTOR (3 downto 0));
end Registro;

architecture Behavioral of Registro is
signal qaux: STD_LOGIC_VECTOR (3 downto 0) := (others => '0');
begin
    --d(3) = OV, d(2)= Z, d(1)=C, d(0)=N
    process(clr,clk,d,qaux,LF)
    begin
        if (clr='1') then
            qaux <= x"0";
        elsif (falling_edge(clk)) then
            if(LF='1') then
                qaux <= d;
            else
                qaux <= qaux;
            end if;
        end if;
        q <= qaux;
    end process;
end Behavioral;
