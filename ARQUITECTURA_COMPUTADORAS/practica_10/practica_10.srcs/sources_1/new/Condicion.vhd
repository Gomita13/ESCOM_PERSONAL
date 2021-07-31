library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Condicion is
    Port ( Q : in STD_LOGIC_VECTOR (3 downto 0);
           EQ,NE,LT,LE,GT,GE : out STD_LOGIC);
end Condicion;

architecture Behavioral of Condicion is
begin
--Q(3)=OV, Q(2)=Z, Q(1)=C, Q(0)=N
    EQ <= Q(2);
    NE <= not Q(2);
    LT <= not Q(1);
    LE <= Q(2) or  (not Q(1));
    GT <= (not Q(2))and Q(1);
    GE <= Q(1);
end Behavioral;
