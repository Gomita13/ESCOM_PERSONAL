library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

package paqueteUC is
component MfunCode is
    Port ( funCode : in STD_LOGIC_VECTOR (3 downto 0);
           MicroInstruccion : out STD_LOGIC_VECTOR (19 downto 0));
end component;
component MopCode is
    Port ( opcode : in STD_LOGIC_VECTOR (4 downto 0);
           MicroInstruccion : out STD_LOGIC_VECTOR (19 downto 0));
end component;
component decod is
  Port (
        opCode: in STD_LOGIC_VECTOR(4 downto 0);
        TIPOR,BEQI,BNEQI,BLTI,BLETI,BGTI,BGETI: out STD_LOGIC
  );
end component;
component UC is 
	Port(
		TIPOR,BEQI,BNEQI,BLTI,BLETI,BGTI,BGETI,NA,EQ,NE,LT,LE,GT,GE,CLR,CLK: in STD_LOGIC;
		SDOPC,SM: out STD_LOGIC
	);
end component;
component nivel is
  Port (
    CLR, CLK: in STD_LOGIC;
    NA: out STD_LOGIC
  );
end component;
component Registro is
    Port ( d : in STD_LOGIC_VECTOR (3 downto 0);
           clr,clk,LF : in STD_LOGIC;
           q : out STD_LOGIC_VECTOR (3 downto 0));
end component;
component Condicion is
    Port ( Q : in STD_LOGIC_VECTOR (3 downto 0);
           EQ,NE,LT,LE,GT,GE : out STD_LOGIC);
end component;
end package;
