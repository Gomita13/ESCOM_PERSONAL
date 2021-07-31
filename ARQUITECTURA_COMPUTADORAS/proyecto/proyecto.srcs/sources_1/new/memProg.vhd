library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity memProg is
    generic (
        p : integer := 9;
        d : integer := 25
    );
    Port ( PC : in STD_LOGIC_VECTOR (p-1 downto 0);
           Inst : out STD_LOGIC_VECTOR (d-1 downto 0));
end memProg;

architecture arq_memProg of memProg is
type aux is array (0 to (2**p)-1) of STD_LOGIC_VECTOR (d-1 downto 0);
--CODIGO DE OPERACION TIPO R
constant OP_R: std_logic_vector (4 downto 0) := "00000";
--CARGA Y ALMACENAMIENTO
constant LI : std_logic_vector (4 downto 0):= "00001";
constant LWI : std_logic_vector (4 downto 0):= "00010";
constant LW : std_logic_vector (4 downto 0):= "10111";
constant SWI :std_logic_vector (4 downto 0):= "00011";
constant SW :std_logic_vector (4 downto 0):= "00100";
--INSTRUCCIONES ARITMETICAS
constant ADD: std_logic_vector (3 downto 0) := "0000";
constant SUB: std_logic_vector (3 downto 0) := "0001";
constant ADDI: std_logic_vector (4 downto 0) := "00101";
constant SUBI: std_logic_vector (4 downto 0) := "00110";
--INSTRUCCIONES LOGICAS
constant rAND: std_logic_vector (3 downto 0) := "0010";
constant r_OR: std_logic_vector (3 downto 0) := "0011";
constant rXOR: std_logic_vector (3 downto 0) := "0100";
constant rNAND: std_logic_vector (3 downto 0) := "0101";
constant rNOR: std_logic_vector (3 downto 0) := "0110";
constant rXNOR: std_logic_vector (3 downto 0) := "0111";
constant rNOT: std_logic_vector (3 downto 0) := "1000";
constant ANDI: std_logic_vector (4 downto 0) := "00111";
constant ORI: std_logic_vector (4 downto 0) := "01000";
constant XORI: std_logic_vector (4 downto 0) := "01001";
constant NANDI: std_logic_vector (4 downto 0) := "01010";
constant NORI: std_logic_vector (4 downto 0) := "01011";
constant XNORI: std_logic_vector (4 downto 0) := "01100";
--INSTRUCCIONES DE CORRIMIENTO
constant rSLL: std_logic_vector (3 downto 0) := "1001";
constant rSRL: std_logic_vector (3 downto 0) := "1010";
--INSTRUCCIONES DE SALTOS CONDICIONALES E INCONDICIONALES
constant BEQI: std_logic_vector (4 downto 0) := "01101";
constant BNEI: std_logic_vector (4 downto 0) := "01110";
constant BLTI: std_logic_vector (4 downto 0) := "01111";
constant BLETI: std_logic_vector (4 downto 0) := "10000";
constant BGTI: std_logic_vector (4 downto 0) := "10001";
constant BGETI: std_logic_vector (4 downto 0) := "10010";
constant B: std_logic_vector (4 downto 0) := "10011";
--INSTRUCCIONES DE MANEJOS DE SUBRUTINAS
constant CALL: std_logic_vector (4 downto 0) := "10100";
constant RET: std_logic_vector (4 downto 0) := "10101";
--OTRAS INSTRUCCIONES
constant NOP: std_logic_vector (4 downto 0) := "10110";
constant S_U: std_logic_vector (3 downto 0) := "0000";

--REGISTROS
constant R0: std_logic_vector (3 downto 0) := "0000";
constant R1: std_logic_vector (3 downto 0) := "0001";
constant R2: std_logic_vector (3 downto 0) := "0010";
constant R9: std_logic_vector (3 downto 0) := "1001";

constant mem : aux := (
   -- PROGRAMA 1
   --LI & R0 & X"0001", -- LI R0,x0
   --LI & R1 & X"0007", -- LI R1,x1
   --OP_R & R1 & R1 & R0 & S_U & ADD, --ADD R1,R1,R0
   --SWI & R1 & x"0005",
   --B & S_U & x"0002",
   -- PROGRAMA 2
   LI & R0 & x"000D", --0
   LI & R1 & x"000A", --1 
   LI & R2 & x"0000", --2
   LI & R9 & x"0000", --3
   OP_R & R9 & R9 & R0 & S_U & ADD, --4 ADD R9,R9,R0
   SW & R9 & R2 & x"000", --5
   ADDI & R2 & R2 & x"001", --6
   BLTI & R1 & R2 & x"3fd", --7
   NOP & S_U & S_U & S_U & S_U & S_U, --8
   B & S_U & x"0008", -- 9
   others => (others => '0')
);

begin
Inst <= mem (conv_integer(PC));

end arq_memProg;
