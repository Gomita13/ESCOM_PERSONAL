library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity sum1Bit is
    Port ( a,b,ci : in STD_LOGIC;
           s,co : out STD_LOGIC);
end sum1Bit;

architecture arq_sum1Bit of sum1Bit is
begin
    s <= a xor b xor ci;
    co <= (a and b) or (a and ci) or (b and ci);
end arq_sum1Bit;
