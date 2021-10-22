--zadanie5
select
sysdate + 4321 as "Za 4321",
sysdate - 4321 as "przeszlosc",
trunc(((sysdate + 4321) - (sysdate - 4321))/7) as tygodni,
trunc(months_between(sysdate + 4321,sysdate - 4321)) as miesiecy,
to_char(sysdate + 4321, 'yyyy-mm-dd d dd ddd day month w ww cc')
from dual;

--zadanie8
select
extract(year from sysdate) as rok,
extract(month from sysdate) as miesiac,
extract(day from sysdate) as dzien,
extract(hour from systimestamp) as godzina,
extract(minute from systimestamp) as minuta,
trunc(extract(second from systimestamp)) as sekunda,
to_char(to_char(sysdate, 'CC'), 'RM') as wiek
from dual;

--zadanie13
select
nazwisko, imiona, data_urodzenia,
extract(year from sysdate)-extract(year from data_urodzenia) as "wg rocznika",
trunc(months_between(sysdate, data_urodzenia)/12) as "pelne lata"
from studenci
where imiona like 'M%' and
trim(to_char(data_urodzenia, 'day')) in ('wtorek', 'czwartek') and
extract(month from data_urodzenia) between 3 and 6
order by data_urodzenia;

--zadanie21
select
nazwisko, stanowisko, data_zatr, data_zwol,
placa+dod_staz*0.01*placa + nvl(dod_funkcyjny, 0) - nvl(koszt_ubezpieczenia, 0) as pensja
from pracownicy
where data_zatr <= TO_DATE('2018-05-01', 'yyyy-mm-dd') and
--nvl(data_zwol, sysdate) > last_day(to_date('2018-06-01', 'yyyy-mm-dd'));
(data_zwol > last_day(to_date('2018-06-01', 'yyyy-mm-dd'))
or data_zwol is null);

--zadanie24
