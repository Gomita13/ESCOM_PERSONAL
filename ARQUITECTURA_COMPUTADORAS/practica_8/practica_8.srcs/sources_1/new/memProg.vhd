library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity memProg is
    generic (
        p : integer := 10;
        d : integer := 25
    );
    Port ( PC : in STD_LOGIC_VECTOR (p-1 downto 0);
           Inst : out STD_LOGIC_VECTOR (d-1 downto 0));
end memProg;

architecture arq_memProg of memProg is
type aux is array (0 to (2**p)-1) of STD_LOGIC_VECTOR (d-1 downto 0);
constant LI : std_logic_vector (4 downto 0):= "00001";
constant R0 : std_logic_vector (3 downto 0):= "0000";
constant R1 : std_logic_vector (3 downto 0):= "0001";
constant R2 : std_logic_vector (3 downto 0):= "0010";
constant R3 : std_logic_vector (3 downto 0):= "0011";
constant R4 : std_logic_vector (3 downto 0):= "0100";
constant OP_R: std_logic_vector (4 downto 0) := "00000";
constant S_U: std_logic_vector (3 downto 0) := "0000";
constant ADD: std_logic_vector (3 downto 0) := "0000";
constant SWI :std_logic_vector (4 downto 0):= "00011";
constant ADDI: std_logic_vector (4 downto 0) := "00101";
constant BNEI: std_logic_vector (4 downto 0) := "01110";
constant NOP: std_logic_vector (4 downto 0) := "10110";
constant B: std_logic_vector (4 downto 0) := "10011";

constant mem : aux := (
   LI & R0 & X"0000", -- LI R0,x0
   LI & R1 & X"0001", -- LI R1,x1
   LI & R2 & X"0000", -- LI R2,x0
   LI & R3 & X"0012", -- LI R3,x12
   OP_R & R4 & R0 & R1 & S_U & ADD, --ADD R4,R0,R1
   SWI & R4 & X"0072", --SWI R4, 0X72
   ADDI & R0 & R1 & X"000", --ADDI R0,R1,x0
   ADDI & R1 & R4 & X"000", --ADDI R1,R4,x0
   ADDI & R2 & R2 & X"001", --ADDI R0,R1,x1
   BNEI & R3 & R2 & X"FFB", --BNEI R3, R2, xFFFB
   NOP & S_U & S_U & S_U & S_U & S_U, --NOP
   B & S_U & x"FFFF", --B xFFFF
   others => (others => '0')
);

begin
Inst <= mem (conv_integer(PC));

end arq_memProg;
