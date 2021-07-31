library IEEE;
library work;
use work.paqueteASM.ALL;
use IEEE.STD_LOGIC_1164.ALL;

entity ASM is
    Port (
        INI,CLK,CLR : in  STD_LOGIC;
        D: in STD_LOGIC_VECTOR(8 downto 0);
        Q: out STD_LOGIC_VECTOR(8 downto 0);
        DIS: out STD_LOGIC_VECTOR(6 downto 0)
	);
end ASM;

architecture arq_ASM of ASM is
component divisor is
  Port (
    reset,clk: in STD_LOGIC;
    dclk: out STD_LOGIC
  );
end component;
signal sA0,sZ,siLA,sLB,sEA,sEB,sEC,sCLK: STD_LOGIC;
signal sQA: STD_LOGIC_VECTOR(8 downto 0);
signal sQB: STD_LOGIC_VECTOR(3 downto 0);
signal sDEC: STD_LOGIC_VECTOR(6 downto 0);
begin
    
    --frecuencia: divisor port map(
        --reset => CLR,
        --clk => CLK,
      --  dclk => sCLK
    --);
    
    sA0 <= sQA(0);
    sZ <= not (sQA(8) or sQA(7) or sQA(6) or sQA(5) or sQA(4) or sQA(3) or sQA(2) or sQA(1) or sQA(0));    

    unidad_control: UC port map(
        a0 => sA0,
        z => sZ,
        ini => INI,
        clk => CLK,
        clr => CLR,
        la => siLA,
        lb => sLB,
        ea => sEA,
        eb => sEB,
        ec => sEC
    );
    
    arreglo_c: arreglo port map(
    da => D, 
    la => siLA,
    ea => sEA,
    clr => CLR,
    clk => CLK,
    qa => sQA
    );
    
    contador_c: contador port map(
       lb => sLB,
       eb => sEB,
       clr => CLR,
       clk => CLK,
       qb => sQB
    );
    
    decodificador: deco port map(
        a => sQB,
        b => sDEC
    );
    
    DIS <= "1111110" when (sEC = '0') else sDEC;
    Q <= sQA;
end arq_ASM;