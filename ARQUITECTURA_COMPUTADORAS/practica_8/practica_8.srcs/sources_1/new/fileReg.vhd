library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;

entity fileReg is
  Port (
  writeData: in STD_LOGIC_VECTOR(15 downto 0);
  writeReg, readReg1, readReg2, shamt: in STD_LOGIC_VECTOR(3 downto 0);
  clk,clr,wr,dir,she: in STD_LOGIC;
  readData1, readData2: out STD_LOGIC_VECTOR(15 downto 0)
  );
end fileReg;

architecture arq_fileReg of fileReg is
type matrix is array (0 to 7) of STD_LOGIC_VECTOR(15 downto 0);
signal registry : matrix;
begin
process (clk, clr)
begin
    -- RESET 
    if(clr = '1') then
        for i in 0 to 7 loop
            registry(i) <= "0000000000000000";
        end loop;
     elsif (rising_edge(clk)) then
        -- CARGA
        if (wr = '1') and (she = '0') then
            registry(CONV_INTEGER(writeReg)) <= writeData;
        elsif (she = '1') and (dir = '1') then 
            -- <<
            registry(CONV_INTEGER(writeReg)) <= TO_STDLOGICVECTOR(TO_BITVECTOR(registry(CONV_INTEGER(readReg2))) sll (CONV_INTEGER(shamt)));
        elsif (she = '1') and (dir = '0') then
            -- >>   
            registry(CONV_INTEGER(writeReg)) <= TO_STDLOGICVECTOR(TO_BITVECTOR(registry(CONV_INTEGER(readReg2))) srl (CONV_INTEGER(shamt)));    
        end if;
     end if;
end process;
readData1 <= registry(CONV_INTEGER(readReg1));
readData2 <= registry(CONV_INTEGER(readReg2));
end arq_fileReg;
