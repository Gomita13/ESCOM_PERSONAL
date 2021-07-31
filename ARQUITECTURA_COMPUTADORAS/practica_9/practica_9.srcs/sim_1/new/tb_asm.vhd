library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_asm is

end tb_asm;

architecture arq_tb_asm of tb_asm is
component ASM is
    Port (
        INI,CLK,CLR : in  STD_LOGIC;
        D: in STD_LOGIC_VECTOR(8 downto 0);
        Q: out STD_LOGIC_VECTOR(8 downto 0);
        DIS: out STD_LOGIC_VECTOR(6 downto 0)
	);
end component;
signal sINI, sCLK, sCLR: STD_LOGIC;
signal sD, sQ: STD_LOGIC_VECTOR(8 downto 0);
signal sDIS: STD_LOGIC_VECTOR(6 downto 0);
begin
    
    instancia: ASM port map(
        INI => sINI,
        CLK => sCLK,
        CLR => sCLR,
        D => sD,
        Q => sQ,
        DIS => sDIS
    );

    reloj: process
    begin
        sCLK <= '0';
        wait for 5 ns;
        sCLK <= '1';
        wait for 5 ns;
    end process;
    
    funcionamiento: process
    begin
        sCLR <= '1';
        wait for 10 ns;
        sCLR <= '0';
        wait for 10 ns;
        sINI <= '1';
        wait for 10 ns;
        sINI <= '0';
        wait for 30 ns;
        sD <= "101101011";
        wait for 70 ns;
        sCLR <= '1';
        wait for 10 ns;
        sCLR <= '0';
        wait for 10 ns;
        sINI <= '1';
        wait for 10 ns;
        sINI <= '0';
        wait for 30 ns;
        sD <= "000011101";
        wait for 70 ns;
        sCLR <= '1';
        wait for 10 ns;
        sCLR <= '0';
        wait for 10 ns;
        sINI <= '1';
        wait for 10 ns;
        sINI <= '0';
        wait for 30 ns;
        sD <= "000010000";
        wait for 70 ns;
        sCLR <= '1';
        wait for 10 ns;
        sCLR <= '0';
        wait for 10 ns;
        sINI <= '1';
        wait for 10 ns;
        sINI <= '0';
        wait for 30 ns;
        sD <= "100001000";
        wait for 70 ns;
        sCLR <= '1';
        wait for 10 ns;
        sCLR <= '0';
        wait for 10 ns;
        sINI <= '1';
        wait for 10 ns;
        sINI <= '0';
        wait for 30 ns;
        sD <= "000000000";
        wait for 70 ns;
    end process;
end arq_tb_asm;
