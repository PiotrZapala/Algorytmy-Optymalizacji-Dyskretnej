using JuMP
using GLPK

struct Dzielnica
    nazwa::String
    min_liczby::Vector{Int}
    max_liczby::Vector{Int}
    min_dla_dzielnic::Int
end
    
struct Zmiana
    numer::Int
    min_dla_zmian::Int
end

function solve_model()

    # wczytanie danych z pliku
    data = readlines("data.txt")

    n_dzielnic = parse.(Int, data[1])
    n_zmian = parse.(Int, data[2])
    dzielnice = [Dzielnica(string(i), parse.(Int, split(data[i+2])),
        parse.(Int, split(data[i + n_dzielnic + 2])),
        parse(Int, data[i + n_dzielnic*n_dzielnic + 2])) for i in 1:n_dzielnic]
    zmiany = [Zmiana(i, parse(Int, data[2*n_zmian + i + 2])) for i in 1:n_zmian]

    # tworzenie modelu
    model = Model(GLPK.Optimizer)
 
    # zmienne decyzyjne
    @variable(model, x[d in dzielnice, z in zmiany] >= 0, Int)
 
    # minimalna liczba radiowozów dla każdej dzielnicy musi być spełniona
    for d in dzielnice
        @constraint(model, sum(x[d, j] for j in zmiany) >= d.min_dla_dzielnic)
    end
 
    # minimalna liczba radiowozów dla każdej zmiany musi być spełniona
    for z in zmiany
        @constraint(model, sum(x[d, z] for d in dzielnice) >= z.min_dla_zmian)
    end
 
    # minimalne i maksymalne liczby radiowozów dla każdej dzielnicy i zmiany muszą być spełnione
    for d in dzielnice, z in zmiany
        @constraint(model, d.min_liczby[z.numer] <= x[d, z] <= d.max_liczby[z.numer])
    end
 
    # minimalizacja liczby radiowozów
    @objective(model, Min, sum(x[d, z] for d in dzielnice, z in zmiany))
 
    # rozwiązanie modelu
    optimize!(model)
 
    # wyświetlenie wyniku
    println("Minimalna liczba radiowozów: ", objective_value(model))
    println("Przydział radiowozów:")
    for d in dzielnice, z in zmiany
        println("Dzielnica ", d.nazwa, ", zmiana ", z.numer, ": ", value(x[d, z]))
    end
 
end

solve_model()