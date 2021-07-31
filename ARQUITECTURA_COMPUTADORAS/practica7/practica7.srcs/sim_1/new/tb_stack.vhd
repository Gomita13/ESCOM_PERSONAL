library IEEE;
LIBRARY STD;
USE STD.TEXTIO.ALL;
USE ieee.std_logic_TEXTIO.ALL;	
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_stack is
end tb_stack;

architecture arq_tb_stack of tb_stack is
component stack is
    Port ( 
        clk, clr, up, dw, wpc : in  STD_LOGIC;
        spOut : out std_logic_vector(2 downto 0);
        pcin : in  STD_LOGIC_VECTOR (15 downto 0);
        pcout : out  STD_LOGIC_VECTOR (15 downto 0)
    );
end component;
signal swpc,sclr,sclk,sup,sdw : STD_LOGIC;
signal spcIn, spcOut : STD_LOGIC_VECTOR (15 downto 0);
signal sspOut: STD_LOGIC_VECTOR(2 downto 0);
begin
    instancia: stack port map (
        wpc => swpc,
        clr => sclr,
        clk => sclk,
        up => sup,
        dw => sdw,
        pcIn => spcIn,
        pcOut => spcOut,
        spOut => sspOut
    );
    CLK_process :process
    begin
		sclk <= '0';
		wait for 10 ns;
		sclk <= '1';
		wait for 10 ns;
    end process;
    
    stim_proc: process
	file ARCH_RES : TEXT;																					
	variable LINEA_RES : line;
	VARIABLE VAR_pcOut : STD_LOGIC_VECTOR (15 downto 0);
    VARIABLE VAR_SP : STD_LOGIC_VECTOR(2 DOWNTO 0);
    	
	file ARCH_VEC : TEXT;
	variable LINEA_VEC : line;
	VARIABLE VAR_WPC,VAR_UP,VAR_DW,VAR_clr: STD_LOGIC;
	VARIABLE VAR_pcIn : STD_LOGIC_VECTOR (15 downto 0);
	
	VARIABLE CADENA : STRING(1 to 4);
   begin		
		file_open(ARCH_VEC, "C:\Users\gamma\Desktop\VECTORES (2).txt", READ_MODE); 	
		file_open(ARCH_RES, "C:\Users\gamma\Desktop\RESULTADO (2).txt", WRITE_MODE); 	
        
		CADENA := "  SP";
		write(LINEA_RES, CADENA, right, CADENA'LENGTH+1);	--ESCRIBE LA CADENA "SP"
		CADENA := "  PC";
		write(LINEA_RES, CADENA, right, CADENA'LENGTH+1);	--ESCRIBE LA CADENA "PC"

		writeline(ARCH_RES,LINEA_RES);-- escribe la linea en el archivo

		WAIT FOR 100 NS;
		FOR I IN 2 TO 27 LOOP --la línea 1 contiene encabezados
			readline(ARCH_VEC,LINEA_VEC); -- lee una linea completa

			read(LINEA_VEC, VAR_clr);
			sclr <= VAR_clr;
			read(LINEA_VEC, VAR_WPC); 
			swpc <= VAR_WPC;		
			read(LINEA_VEC, VAR_UP); 
			sup <= VAR_UP;			
			read(LINEA_VEC, VAR_DW); 
			sdw <= VAR_DW;	
			hread(LINEA_VEC, VAR_pcIn); 
			spcIn <= VAR_pcIn;	
			
			WAIT UNTIL RISING_EDGE(sCLK);	--ESPERO AL FLANCO DE SUBIDA 

			VAR_pcOut := spcOut;	
			VAR_SP := sspOut;
			hwrite(LINEA_RES, VAR_SP, right, 5);	--ESCRIBE EL CAMPO SP
			hwrite(LINEA_RES, VAR_pcOut, right, 5);	--ESCRIBE EL CAMPO pcOut
				
			writeline(ARCH_RES,LINEA_RES);-- escribe la linea en el archivo
			
		end loop;
		file_close(ARCH_VEC);  -- cierra el archivo
		file_close(ARCH_RES);  -- cierra el archivo

      wait;
   end process;

end arq_tb_stack;
