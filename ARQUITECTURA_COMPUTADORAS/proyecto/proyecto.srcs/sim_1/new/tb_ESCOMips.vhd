library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_ESCOMips is
end tb_ESCOMips;

architecture arq_tb_ESCOMips of tb_ESCOMips is
component ESCOMips is
    Port ( rclr,clk: in STD_LOGIC;
           reDa1,reDa2,busSR,resALU: out std_logic_vector (15 downto 0);
           PC : out std_logic_vector (9 downto 0);
           instruccion: out std_logic_vector (24 downto 0);
           Micro: out std_logic_vector(19 downto 0)
    );
end component;
signal sCLK, sRCLR: STD_LOGIC := '0';
signal MICROINST : STD_LOGIC_VECTOR(19 downto 0) := (others => '0');
signal sREDA1,sREDA2,sRESALU,sBUSSR: STD_LOGIC_VECTOR(15 downto 0) := (others => '0');
signal sPC: STD_LOGIC_VECTOR(9 downto 0) := (others => '0');
signal sINST: STD_LOGIC_VECTOR(24 downto 0) := (others => '0');
begin
    
    instancia: ESCOMips port map(
        clk => sCLK,
        rclr=> sRCLR,
        pc => sPC,
        reDa1 => sREDA1,
        reDa2 => sREDA2,
        resALU => sRESALU, 
        busSR => sBUSSR,
        instruccion => sINST,
        Micro => MICROINST
    );
    
    reloj: process
    begin
        sCLK <= '0';
        wait for 10 ns;
        sCLK <= '1';
        wait for 10 ns;
    end process;
    
    funcion: process
    begin
        sRCLR <= '1';
        wait for 30 ns;
        sRCLR <= '0';
        wait;
    end process;
end arq_tb_ESCOMips;
