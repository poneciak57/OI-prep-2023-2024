/**
 * Jesli mamy przed soba zadanie w ktorym musimy sprawdzic czy istnieje jakies zapalenie n bitow takich jak
 * a1, a2, a3, ... , an
 * ze zachodzi ciag zalozen postaci
 * (a1 || a2) && (!a2 || !a3) && ... etc
 * 
 * Mozemy stworzyc graf koniunkcji implikacji:
 * Jesli istnieje implikacja v => w to tworzymy krawedz od wierzcholka v do w
 * implikacja oznacza ze dla v = 0, w musi sie rownac 1
 * 
 * Graf bedzie mial 2*n wierzcholkow gdyz mamy takze wierzcholki dla negacji
 * Dzielimy taki graf na spojnie skladowe 
 * Sortujemy spojnie skladowe topologicznie
 * SCC_ind(v) -> indeks spojnej danego wierzcholka w sortowaniu topologicznym
 * 
 * OPCJE:
 * 1. Sprawdzanie istnienia rozwiazania
 * Jesli dla ktorej kolwiek zmienej x i !x sa w tej samej spojnie skladowej rozwiazanie nie istnieje
 * 
 * 2. Okreslenie wartosci zmiennych
 * Jesli SCC_ind(x) < SCC_ind(!x) to wartosc musi zostac ustawiona na 1 => prawda
 * Jesli SCC_ind(x) > SCC_ind(!x) to wartosc musi zostac ustawiona na 0 => falsz
 * 
 * 3. Ilosc poprawnych rozwiazan (nie zawsze mozliwe do okreslenia)
 * 
 * 
 * 
 * TRICKI:
 * 1. Albo obie zachodza albo żadna nie zachodzi
 * (!xi || xj) && (xi || !xj)
 * 
 * 2. Dokładnie jeden warunek zachodzi
 * (xi || xj) && (!xi || !xj)
*/