using JuMP
using GLPK

function solve_model()

    # wczytanie danych z pliku
    data = readlines("data.txt")
 
    # parsowanie danych
    n = parse.(Int, data[1])
    m = parse.(Int, data[2])
    k = parse.(Int, data[3])
    s_split = [split(str, " ") for str in data[4:end]]
    occupied =[(parse(Int, x[1]), parse(Int, x[2])) for x in s_split]

    # tworzenie modelu
    model = Model(GLPK.Optimizer)

    # Zmienne decyzyjne: 1, jeśli w danym kwadracie umieszczona jest kamera, 0 w przeciwnym wypadku
    @variable(model, x[1:m, 1:n], Bin)

    # Ograniczenie: każdy kontener musi być monitorowany przez co najmniej jedną kamerę
    for (i, j) in occupied
        neighbors = []
        for r in max(1, i-k):min(m, i+k)
            for c in max(1, j-k):min(n, j+k)
                if abs(i-r) + abs(j-c) <= k && (i, j) != (r, c)
                    push!(neighbors, x[r, c])
                end
            end
        end
        @constraint(model, sum(neighbors) >= 1)
    end

    # Funkcja celu: minimalizacja liczby użytych kamer
    @objective(model, Min, sum(x))

    optimize!(model)

    # Wypisanie wyniku
    println("Liczba użytych kamer: ", objective_value(model))
    for i in 1:m
        for j in 1:n
            if (i, j) in occupied
                print("C ")
            elseif value(x[i, j]) > 0
                print("K ")
            else
                print("- ")
            end
        end
        println()
    end
end

solve_model()