library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

package paqueteASM is
component UC is
    Port ( a0,z,ini,clk,clr : in  STD_LOGIC;
           la,lb,ea,eb,ec : out  STD_LOGIC	
	);
end component;
component arreglo is
  Port (
    DA: in STD_LOGIC_VECTOR(8 downto 0);
    LA,EA,CLR,CLK: in STD_LOGIC;
    QA: out STD_LOGIC_VECTOR(8 downto 0)
  );
end component;
component deco is
  Port (
    A: in STD_LOGIC_VECTOR(3 downto 0);
    B: out STD_LOGIC_VECTOR(6 downto 0)
  );
end component;
component contador is
  Port (
    LB, EB, CLR, CLK: in STD_LOGIC;
    QB: out STD_LOGIC_VECTOR(3 downto 0)    
  );
end component;
end package;
