#include <string>
#include "genetic.hpp"
#include <fstream>

using namespace std;


struct MyGenes
{
	double X,Y,Z;

	std::string to_string() const
	{
		return 
			" {x:"+std::to_string(X)+
		    ",y:"+std::to_string(Y)+
			",z:"+std::to_string(Z)+
			"} ";
	}
};

struct MyMiddleCost
{
	double X,Y,Z;
};

typedef EA::Genetic<MyGenes,MyMiddleCost> GA_Type;
typedef EA::GenerationType<MyGenes,MyMiddleCost> Generation_Type;

void init_genes(MyGenes& p,const std::function<double(void)> &rand)
{
	p.X=10*rand();
	p.Y=10*rand();
	p.Z=10*rand();
}


bool eval_genes(
	const MyGenes& p,
	MyMiddleCost &c)
{
	double x = p.X, y = p.Y, z = p.Z;

	double n = x+y+z;
	
	if(n > 9 && n < 9.5){
		c.X = x;
		c.Y = y;
		c.Z = z;
		return true;
	}
	else{
		return false; // genes are accepted
	}
}


MyGenes mutate(
	const MyGenes& X_base,
	const std::function<double(void)> &rand,
	double shrink_scale)
{
	MyGenes New_gene;
	(void) shrink_scale;
	bool in_range_X,in_range_Y,in_range_Z;
	do{
		New_gene=X_base;
		New_gene.X+=10*(rand()-rand());
		New_gene.Y+=10*(rand()-rand());
		New_gene.Z+=10*(rand()-rand());
		in_range_X= (New_gene.X>=0.0 && New_gene.X<200.0);
		in_range_Y= (New_gene.Y>=0.0 && New_gene.Y<200.0);
		in_range_Z= (New_gene.Z>=0.0 && New_gene.Z<200.0);
	} while(!in_range_X || !in_range_Y || !in_range_Z);
	return New_gene;
}

MyGenes crossover(
	const MyGenes& X1,
	const MyGenes& X2,
	const std::function<double(void)> &rand)
{
	MyGenes New_gene;
	double r;
	r=rand();
	New_gene.X=r*X1.X+(1.0-r)*X2.X;
	r=rand();
	New_gene.Y=r*X1.Y+(1.0-r)*X2.Y;
	r=rand();
	New_gene.Z=r*X1.Z+(1.0-r)*X2.Z;
	return New_gene;
}

double calculate_SO_total_fitness(const GA_Type::thisChromosomeType &X)
{
	// finalize the cost
	double costX,costY,costZ;
	costX=X.middle_costs.X;
	costY=X.middle_costs.Y;
	costZ=X.middle_costs.Z;

	// cout << "calculate_SO_total_fitness:" << " "; 
	// cout << costX+costY+costZ << endl; 
	return costX+costY+costZ;
}

std::ofstream output_file;

void SO_report_generation(
	int generation_number,
	const EA::GenerationType<MyGenes,MyMiddleCost> &last_generation,
	const MyGenes& best_genes)
{
	std::cout
		<<"Generation ["<<generation_number<<"],\t"
		<<"Best="<<last_generation.best_total_cost<<",\t"
		<<"Average="<<last_generation.average_cost<<",\t"
		<<"Best genes=("<<best_genes.to_string()<<")"<<",\t"
		<<"Exe_time="<<last_generation.exe_time
		<<std::endl;

	// output_file
	// 	<<generation_number<<"\t"
	// 	<<best_genes.to_string()<<"\t"
	// 	<<100.0-last_generation.average_cost<<"\t"
	// 	<<100.0-last_generation.best_total_cost<<"\n";
	output_file
		<<generation_number<<"\t"
		<<"{"
		<<best_genes.X<<","
		<<best_genes.Y<<","
		<<best_genes.Z<<""
		<<"}\t"
		<<last_generation.average_cost<<"\t"
		<<last_generation.best_total_cost<<"\n";
}

int main(int argc, char const *argv[]){
	// cout << "Hello world!" << endl;
	// for (int i = 0; i < argc; ++i)
	// 	cout << argv[i] << endl;
	
	// output_file.open("./bin/result_so-rastrigin.txt");
	output_file.open("../myBin/main.txt");
	output_file
		<<"step"
		<<"\t"
		<<"position_best"
		<<"\t"
		<<"cost_avg"
		<<"\t"
		<<"cost_best"
		<<"\n";

	EA::Chronometer timer;
	timer.tic();

	GA_Type ga_obj;
	ga_obj.problem_mode=EA::GA_MODE::SOGA;
	ga_obj.multi_threading=true;
	ga_obj.dynamic_threading=false;
	ga_obj.idle_delay_us=0; // switch between threads quickly
	ga_obj.verbose=false;

	ga_obj.population=100;
	ga_obj.generation_max=1000;

	ga_obj.calculate_SO_total_fitness=calculate_SO_total_fitness;
	ga_obj.init_genes=init_genes;
	ga_obj.eval_genes=eval_genes;
	ga_obj.mutate=mutate;
	ga_obj.crossover=crossover;
	ga_obj.SO_report_generation=SO_report_generation;
	ga_obj.best_stall_max=20;
	ga_obj.average_stall_max=20;
	ga_obj.tol_stall_best=1e-6;
	ga_obj.tol_stall_average=1e-6;
	ga_obj.elite_count=1;
	ga_obj.crossover_fraction=0.75;
	ga_obj.mutation_rate=0.05;
	ga_obj.solve();

	std::cout<<"The problem is optimized in "<<timer.toc()<<" seconds."<<std::endl;

	output_file.close();
	return 0;
}