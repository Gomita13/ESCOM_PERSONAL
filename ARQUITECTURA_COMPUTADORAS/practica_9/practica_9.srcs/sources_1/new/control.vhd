library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity UC is
    Port ( a0,z,ini,clk,clr : in  STD_LOGIC;
           la,lb,ea,eb,ec : out  STD_LOGIC	
			  );
end UC;

architecture Behavioral of UC is

type estados is (e0,e1,e2);
signal actual,siguiente: estados;
begin
    process(clr,clk)
    begin
        if(clr='1') then
            actual<=e0;
        elsif (rising_edge(clk)) then
            actual<=siguiente;
        end if;
    end process;
	
    process (actual,ini,z,a0)
    begin
        la<='0';
        lb<='0';
        ea<='0';
        eb<='0';
        ec<='0';
        case actual is
            when e0=>
                lb<='1';
                if (ini='1') then
                    siguiente<=e1;
                else 
                    la<='1';
                    siguiente<=e0;
                end if;
            when e1 =>
                ea<='1';
                if (z='0') then
                    if (a0='1') then
                        eb<='1';
                        siguiente<=e1;
                    else
                        siguiente<=e1;
                    end if;
                else
                    siguiente<=e2;
                end if;
            when e2 =>
                ec<='1';
                if (ini='1') then
                    siguiente<=e2;
                else
                    siguiente<=e0;
                end if;
        end case;
    end process;
    
end Behavioral;