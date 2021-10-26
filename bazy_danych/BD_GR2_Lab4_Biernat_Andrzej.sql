--zadanie3
select *
from pracownicy join stanowiska using(stanowisko)
where placa not between placa_min and placa_max;

select count(*) from rejestry full join gatunki using(id_gatunku);

--zadanie6
select *
from licencje join wedkarze using(id_wedkarza)
where rodzaj = 'podstawowa' and rok=extract(year from sysdate)
and od_dnia='01-01' and do_dnia='31-12' and id_okregu like 'PZW%';

--zadanie9
select p1.nr_akt, p1.id_dzialu, p1.placa, p2.nr_akt, p2.id_dzialu, p2.placa
from pracownicy p1 cross join pracownicy p2
where p1.id_dzialu = 20 and p2.id_dzialu = 30;

select p1.nr_akt, p1.id_dzialu, p1.placa, p2.nr_akt, p2.id_dzialu, p2.placa
from pracownicy p1 join pracownicy p2
on p1.nr_akt != p2.nr_akt
where p1.id_dzialu = 20 and p2.id_dzialu = 30;

--zadanie15
select extract(year from czas), to_char(czas, 'day'),
count(*), count(id_gatunku)
from rejestry
where mod(extract(month from czas), 2) = 0
group by extract(year from czas), to_char(czas, 'day')
order by 3 desc, 4 desc;

--zadanie18
select
substr(adres, regexp_instr(adres, '[[:digit:]](\s[[:alpha:]]{1,})?\s[[:alpha:]]{1,}$')+2),
count(nr_akt), count(koszt_ubezpieczenia), sum(placa)
from pracownicy RIGHT join dzialy using(id_dzialu)
group by substr(adres, regexp_instr(adres, '[[:digit:]](\s[[:alpha:]]{1,})?\s[[:alpha:]]{1,}$')+2);

--zadanie12
select tryb, kierunek, count(*)
from studenci
group by kierunek, tryb
having count(*) >= 100
order by 3;

--zadanie24
select id_wlasciciela, wlasciciel, count(vin), count(DISTINCT(marka))
from pojazdy right join wlasciciele using (id_wlasciciela)
where status_wlasciciela = 'osoba_fizyczna'
group by id_wlasciciela, wlasciciel
having count(vin) = 0 or count(vin) = 3 and count(marka) = 3;