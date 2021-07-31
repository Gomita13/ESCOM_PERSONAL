library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

package paqueteCPU is
component pila is
    generic (
        p: integer := 16;
        q: integer := 8
    );
    Port ( 
        clk, clr, up, dw, wpc : in  STD_LOGIC;
        pcin : in  STD_LOGIC_VECTOR (p-1 downto 0);
        pcout : out  STD_LOGIC_VECTOR (p-1 downto 0)
    );
end component;
component memProg is
    generic (
        p : integer := 9;
        d : integer := 25
    );
    Port ( PC : in STD_LOGIC_VECTOR (p-1 downto 0);
           Inst : out STD_LOGIC_VECTOR (d-1 downto 0));
end component;
component alu is
    generic (
        p: integer := 16
    );    
    Port ( 
    a,b: in STD_LOGIC_VECTOR(p-1 downto 0);
    --Recordamos que co = c
    co,ov,z,n: out STD_LOGIC;
    --Recordamos cin = selb = op(2)
    op: in STD_LOGIC_VECTOR(3 downto 0);
    s : out STD_LOGIC_VECTOR(p-1 downto 0)
);
end component;
component fileReg is
  Port (
  writeData: in STD_LOGIC_VECTOR(15 downto 0);
  writeReg, readReg1, readReg2, shamt: in STD_LOGIC_VECTOR(3 downto 0);
  clk,clr,wr,dir,she: in STD_LOGIC;
  readData1, readData2: out STD_LOGIC_VECTOR(15 downto 0)
  );
end component;
component memDatos is
    generic (
        p : integer := 9;
        d : integer := 16
    );
    Port ( add : in STD_LOGIC_VECTOR (p-1 downto 0);
           dataIn : in STD_LOGIC_VECTOR (d-1 downto 0);
           WD,clk : in STD_LOGIC;
           dataOut : out STD_LOGIC_VECTOR (d-1 downto 0));
end component;
component ext_signo is
    Port(
        lit: in STD_LOGIC_VECTOR(11 downto 0);
        litExt: out STD_LOGIC_VECTOR(15 downto 0)
    );
end component;
component ext_dir is
  Port (
    dir: in STD_LOGIC_VECTOR(11 downto 0);
    dirExt: out STD_LOGIC_VECTOR(15 downto 0)
   );
end component;
component P11 is
    port (
    opcode : in STD_LOGIC_VECTOR (4 downto 0);
    funcode,Banderas : in STD_LOGIC_VECTOR (3 downto 0);
    CLR,CLK: in STD_LOGIC;
    MicroInstruccion: out std_logic_vector (19 downto 0)
    );
end component;
end package;
