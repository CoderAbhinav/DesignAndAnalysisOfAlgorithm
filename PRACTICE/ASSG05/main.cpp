#include <iostream>
#include <vector>
#include <string>
#include <random>

bool compareGene(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
{
    return a.second < b.second;
}

class TSPGeneticImplementation
{
#define Graph std::vector<std::vector<int>>
#define Gene std::string
#define Individual std::pair<Gene, int>

private:
    int numberOfCities, start, populationSize, temparature, temparatureThreshold, generationThreshold;
    double coolDownFactor;
    Graph graph;
    std::vector<std::pair<std::vector<Individual>, int>> generations;

    /**
     * @brief performs mutation of genes randomly
     *
     * @param gnome parent gene
     * @return string mutated gene
     */
    Gene mutatedGene(Gene gene)
    {
        while (true)
        {
            int r1 = TSPGeneticImplementation::randomNumberGenerator(1, numberOfCities);
            int r2 = TSPGeneticImplementation::randomNumberGenerator(1, numberOfCities);

            if (r1 != r2)
            {
                char temp = gene[r1];
                gene[r1] = gene[r2];
                gene[r2] = temp;
                break;
            }
        }

        return gene;
    }

    /**
     * @brief Create a Gene from root randomly
     *
     * @return string
     */
    Gene createGenome()
    {

        Gene gnome = "0";
        while (true)
        {
            if (gnome.size() == numberOfCities)
            {
                gnome += gnome[0];
                break;
            }

            int temp = TSPGeneticImplementation::randomNumberGenerator(1, numberOfCities);
            if (!repeat(gnome, (char)(temp + 48)))
            {
                gnome += (char)(temp + 48);
            }
        }

        return gnome;
    }

    /**
     * @brief Calculates fitness of given Gene
     *
     * @param gnome gene
     * @return int fitness score of gene
     */
    int calculateFitness(Gene gene)
    {
        int fitness = 0;
        for (int i = 0; i < gene.size() - 1; i++)
        {
            if (graph[gene[i] - 48][gene[i + 1] - 48] == INT_MAX)
            {
                return INT_MAX;
            }
            fitness += graph[gene[i] - 48][gene[i + 1] - 48];
        }

        return fitness;
    }

    /**
     * @brief Function cools down the temperature
     *
     * @return int return updated temperature
     */
    int cooldown()
    {
        return temparature = (coolDownFactor * temparature);
    }

    void SolutionBuilder()
    {
        int gen = 1;

        std::vector<Individual> population;

        for (int i = 0; i < populationSize; i++)
        {

            Gene gene = createGenome();
            std::cout << "GENE GENERATED is " << gene << "\n";
            Individual temp = make_pair(gene, calculateFitness(gene));
            population.push_back(temp);
        }

        while (temparature > temparatureThreshold && gen <= generationThreshold)
        {

            std::cout << "TEMP\t" << temparature << ", GEN\t" << gen << "\n";
            // generations.push_back(make_pair(population, temparature));
            sort(population.begin(), population.end(), compareGene);

            std::cout << "GENE\tFITNESS\n";
            for (int i = 0; i < population.size(); i++)
            {
                std::cout << population[i].first << "\t" << population[i].second << "\n";
            }

            std::vector<Individual> newPopulation;

            for (int i = 0; i < populationSize; i++)
            {
                Individual individual = population[i];

                while (true)
                {
                    Gene newGene = mutatedGene(individual.first);
                    int newGeneFitness = calculateFitness(newGene);

                    if (newGeneFitness <= individual.second)
                    {
                        newPopulation.push_back(make_pair(newGene, newGeneFitness));
                        break;
                    }
                    else
                    {
                        float prob = pow(2.7, -1 * ((float)(newGeneFitness - individual.second) / temparature));

                        if (prob > 0.5)
                        {
                            newPopulation.push_back(make_pair(newGene, newGeneFitness));
                            break;
                        }
                    }
                }
            }

            cooldown();
            population = newPopulation;
            gen++;
        }

        generations.push_back(make_pair(std::vector<Individual>(population.begin(), population.end()), temparature));
    }

protected:
    /**
     * @brief generates a random number
     *
     * @param start range start
     * @param end range end
     * @return int
     */
    static int randomNumberGenerator(int start, int end)
    {
        int r = end - start;
        int rnum = start + rand() % r;
        return rnum;
    }

    /**
     * @brief Function checks if given character is already present in string
     *
     * @param s
     * @param c
     * @return bool
     */
    static bool repeat(std::string s, char c)
    {
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == c)
                return true;
        }

        return false;
    }

public:
    TSPGeneticImplementation(
        Graph graph,
        int populationSize,
        int temparature,
        double coolDownFactor = 0.9,
        int temparatureThreshold = -1,
        int generationThreshold = -1)
    {
        this->graph = graph;
        this->populationSize = populationSize;
        this->temparature = temparature;

        this->numberOfCities = graph.size();

        this->temparatureThreshold = temparatureThreshold == -1 ? 0.1 * temparature : temparatureThreshold;
        this->coolDownFactor = coolDownFactor;
        this->generationThreshold = generationThreshold == -1 ? populationSize : generationThreshold;

        SolutionBuilder();
    }

    std::vector<std::pair<std::vector<Individual>, int>> getGenerations()
    {
        return generations;
    }
};

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> graph = {{0, 2, INT_MAX, 12, 5},
                                           {2, 0, 4, 8, INT_MAX},
                                           {INT_MAX, 4, 0, 3, 3},
                                           {12, 8, 3, 0, 10},
                                           {5, INT_MAX, 3, 10, 0}};

    TSPGeneticImplementation imp(graph, 10, 10000, 0.9, 1000, 5);

    auto generation = imp.getGenerations();

    // for (int i = 0; i < generation.size(); i++)
    // {
    //     std::cout << "\n\nGENERATION is " << i << "\n";
    //     std::cout << "TEMPERATURE is " << generation[i].second << "\n";
    //     std::cout << "GENE\tFITNESS\n";

    //     // for (int j = 0; j < generation[i].first.size(); j++)
    //     // {
    //     //     std::cout << generation[i].first[i].first << "\t" << generation[i].first[i].second << "\n";
    //     // }
    // }
    return 0;
}
