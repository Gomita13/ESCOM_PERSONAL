library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_arith.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;
entity MfunCode is
    Port ( funCode : in STD_LOGIC_VECTOR (3 downto 0);
           MicroInstruccion : out STD_LOGIC_VECTOR (19 downto 0));
end MfunCode;

architecture Behavioral of MfunCode is
type arreglo is array  (0 to 15) of STD_LOGIC_VECTOR (19 downto 0);
constant memFunCode: arreglo := (
   "00000100010000110011", --ADD: 00
   "00000100010001110011", --SUB: 01 
   "00000100010000000011", --AND: 02
   "00000100010000010011", --OR: 03
   "00000100010000100011", --XOR: 04
   "00000100010011010011", --NAND: 05
   "00000100010011000011" , --NOR: 06
   "00000100010010100011", --XNOR: 07
   "00000100010011010011", --NOT: 08
   "00000001110000000000", --SLL: 09
   "00000001010000000000", --SRL: 10      
    others=>(others=>'0')
 );
begin
MicroInstruccion <= memFunCode (conv_integer(funCode));

end Behavioral;
