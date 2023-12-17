using JuMP
using GLPK

function solve_model()

    # wczytywanie danych z pliku
    data = readlines("data.txt")

    # parsowanie danych
    dane_ograniczenia = [parse(Int, x) for x in split(data[1])]
    dane_popytu = [parse(Int, x) for x in split(data[2])]
    s_split = [split(str, " ") for str in data[3:end]]
    dane_kosztow = [[parse(Int, x) for x in row] for row in s_split]

    # tworzenie modelu
    model = Model(GLPK.Optimizer)

    # definicja zmiennych decyzyjnych
    m = length(dane_ograniczenia)
    n = length(dane_popytu)
    @variable(model, x[1:m, 1:n] >= 0)

    # definicja funkcji celu
    koszty = hcat(dane_kosztow...)
    @objective(model, Min, sum(koszty[i,j]*x[i,j] for i in 1:m, j in 1:n))

    # definicja ograniczeń
    for i in 1:m
        @constraint(model, sum(x[i,:]) <= dane_ograniczenia[i])
    end

    for j in 1:n
        @constraint(model, sum(x[:,j]) >= dane_popytu[j])
    end

    # rozwiązanie modelu
    optimize!(model)

    # wyświetlenie wyników
    println("Minimalny koszt: ", objective_value(model))
    for j in 1:n
        println("Dostawa paliwa na lotnisko ", j, ": ")
        for i in 1:m
            println("\tFirma ", i, ": ", value(x[i,j]), " galonów")
        end
    end
end

solve_model()