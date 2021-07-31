library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity arreglo is
  Port (
    DA: in STD_LOGIC_VECTOR(8 downto 0);
    LA,EA,CLR,CLK: in STD_LOGIC;
    QA: out STD_LOGIC_VECTOR(8 downto 0)
  );
end arreglo;

architecture arq_arreglo of arreglo is
signal sQA: STD_LOGIC_VECTOR(8 downto 0);
begin
process (CLK,CLR,sQA)
begin
    if (CLR = '1') then
        sQA <= "000000000";
    elsif (rising_edge(CLK)) then
        if(LA = '0') and (EA = '1') then
            sQA <= to_stdlogicvector(to_bitvector(sQA) srl 1);
        elsif (LA = '1') and (EA = '0') then
            sQA <= DA;        
        end if;
    end if; 
    QA <= sQA;
end process;
end arq_arreglo;
