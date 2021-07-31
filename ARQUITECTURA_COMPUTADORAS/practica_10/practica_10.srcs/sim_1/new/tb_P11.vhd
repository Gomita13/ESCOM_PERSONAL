library IEEE;
LIBRARY STD;
USE STD.TEXTIO.ALL;
USE ieee.std_logic_TEXTIO.ALL;	
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_P11 is
end tb_P11;

architecture arq_tb_P11 of tb_P11 is
component P11 is
    port (
    opcode : in STD_LOGIC_VECTOR (4 downto 0);
    funcode,Banderas : in STD_LOGIC_VECTOR (3 downto 0);
    CLR,CLK,LF: in STD_LOGIC;
    MicroInstruccion: out std_logic_vector (19 downto 0)
    );
end component;
signal sOPCODE: STD_LOGIC_VECTOR(4 downto 0); 
signal sFUNCODE, sBANDERAS: STD_LOGIC_VECTOR(3 downto 0); 
signal sCLR, sCLK, sLF: STD_LOGIC; 
signal sMICRO: STD_LOGIC_VECTOR(19 downto 0);
begin

instancia: P11 port map(
    opCode => sOPCODE,
    funcode => sFUNCODE,
    Banderas => sBANDERAS,
    CLR => sCLR,
    CLK => sCLK,
    LF => sLF,
    MicroInstruccion => sMICRO
);

reloj: process
begin 
    sCLK <= '0';
    wait for 10 ns;
    sCLK <= '1';
    wait for 10 ns;
end process;

funcionamiento: process
    file ARCH_RES : TEXT;																					
	variable LINEA_RES : line;
	VARIABLE VAR_MICRO: STD_LOGIC_VECTOR(19 downto 0);
	VARIABLE VAR_NIVEL: STRING (1 to 4);
    file ARCH_VEC : TEXT;
	variable LINEA_VEC : line;
	VARIABLE VAR_OPCODE: STD_LOGIC_VECTOR(4 downto 0);
	VARIABLE VAR_FUNCODE,VAR_BANDERAS: STD_LOGIC_VECTOR(3 downto 0);
	VARIABLE VAR_CLR, VAR_LF: STD_LOGIC;
	VARIABLE CADENA: STRING(1 to 8);
	VARIABLE CADENAMICRO: STRING(1 to 19);
begin
    file_open(ARCH_VEC, "C:\Users\gamma\Desktop\VECT.txt", READ_MODE); 	
	file_open(ARCH_RES, "C:\Users\gamma\Desktop\RES.txt", WRITE_MODE); 	
	CADENA := "OP_CODE ";
    write(LINEA_RES, CADENA, right, CADENA'LENGTH+1);	--ESCRIBE LA CADENA "OP_CODE"
    CADENA := "FUNCODE ";
    write(LINEA_RES, CADENA, right, CADENA'LENGTH+1);	--ESCRIBE LA CADENA "FNCODE"
    CADENA := "BANDERAS";
    write(LINEA_RES, CADENA, right, CADENA'LENGTH+1);	--ESCRIBE LA CADENA "BANDRS"
    CADENA := "CLR     ";
    write(LINEA_RES, CADENA, right, CADENA'LENGTH+1);	--ESCRIBE LA CADENA "CLR   "
    CADENA := "LF      ";
    write(LINEA_RES, CADENA, right, CADENA'LENGTH+1);	--ESCRIBE LA CADENA "LF    "
    CADENA := "MICROINS";
    write(LINEA_RES, CADENA, right, CADENA'LENGTH+1);	--ESCRIBE LA CADENA "MICROI"
    CADENAMICRO := "              NIVEL";
    write(LINEA_RES, CADENA, right, CADENA'LENGTH+1);	--ESCRIBE LA CADENA "NIVEL "
    writeline(ARCH_RES,LINEA_RES);-- escribe la linea en el archivo
    
    while not (endfile(ARCH_VEC)) loop
        readline(ARCH_VEC,LINEA_VEC); -- lee una linea completa
        read(LINEA_VEC,VAR_OPCODE);
        sOPCODE <= VAR_OPCODE;
        read(LINEA_VEC, VAR_FUNCODE); 
        sFUNCODE <= VAR_FUNCODE;		
        read(LINEA_VEC, VAR_BANDERAS); 
        sBANDERAS <= VAR_BANDERAS;			
        read(LINEA_VEC, VAR_CLR); 
        sCLR <= VAR_CLR;	
        read(LINEA_VEC,VAR_LF);
        sLF <= VAR_LF; 
        
        wait until rising_edge(sCLK);
        
        VAR_MICRO := sMICRO;
        VAR_NIVEL := "ALTO"; 
        write(LINEA_RES, VAR_OPCODE, left, 10);	--ESCRIBE LA CADENA "OP_CODE"
        write(LINEA_RES, VAR_FUNCODE, left, 9);	--ESCRIBE LA CADENA "FNCODE"
        write(LINEA_RES, VAR_BANDERAS, left, 10);	--ESCRIBE LA CADENA "BANDRS"
        write(LINEA_RES, VAR_CLR, left, 8);	--ESCRIBE LA CADENA "CLR   "
        write(LINEA_RES, VAR_LF, left, 9);	--ESCRIBE LA CADENA "LF    "
        write(LINEA_RES, VAR_MICRO, left, 22);	--ESCRIBE LA CADENA "MICROI"
        write(LINEA_RES, VAR_NIVEL, left, 5);	--ESCRIBE LA CADENA "NIVEL "
        writeline(ARCH_RES,LINEA_RES);-- escribe la linea en el archivo
        
        wait until falling_edge(sCLK);
        
        VAR_MICRO := sMICRO;
        VAR_NIVEL := "BAJO";
        write(LINEA_RES, VAR_OPCODE, left, 10);	--ESCRIBE LA CADENA "OP_CODE"
        write(LINEA_RES, VAR_FUNCODE, left, 9);	--ESCRIBE LA CADENA "FNCODE"
        write(LINEA_RES, VAR_BANDERAS, left, 10);	--ESCRIBE LA CADENA "BANDRS"
        write(LINEA_RES, VAR_CLR, left, 8);	--ESCRIBE LA CADENA "CLR   "
        write(LINEA_RES, VAR_LF, left, 9);	--ESCRIBE LA CADENA "LF    "
        write(LINEA_RES, VAR_MICRO, left, 22);	--ESCRIBE LA CADENA "MICROI"
        write(LINEA_RES, VAR_NIVEL, left, 5);	--ESCRIBE LA CADENA "NIVEL "
        writeline(ARCH_RES,LINEA_RES);-- escribe la linea en el archivo
        
    end loop;
    file_close(ARCH_RES);
    file_close(ARCH_VEC);
    wait;
end process;

end arq_tb_P11;
