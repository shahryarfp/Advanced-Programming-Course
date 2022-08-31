#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

#define not_in_karvash -1
#define finished -2
#define zero 0

class Car {
public:
	Car(int id, int coefficient) {
		car_id = id;
		luxury_coefficient = coefficient;
		cars_stage = not_in_karvash;
		is_in_process = false;
	}
	int find_cars_stage() {
		return cars_stage;
	}
	bool find_is_in_process() {
		return is_in_process;
	}
	void step_with_no_stage(int stages_size,int not_entered_cars) {
		if (stages_size == 0) {
			cars_stage = finished;
			not_entered_cars--;
		}
	}
	void go_to_first_stage() {
		cars_stage++;
	}
	int find_luxury_coefficient() {
		return luxury_coefficient;
	}
	void go_into_progress() {
		is_in_process = true;
	}
	int find_car_id() {
		return car_id;
	}
	void go_to_next_stage(int stages_size) {
		is_in_process = false;
		if (cars_stage + 1 == stages_size) {
			cars_stage = finished;
		}
		else {
			cars_stage++;
		}
	}
private:
	int car_id;
	int luxury_coefficient;
	int cars_stage;
	bool is_in_process;
};

class Worker {
public:
	Worker(int id, int time_coefficient,Car c):worker_car(c) {
		worker_id = id;
		worker_time_coefficient = time_coefficient;
		time_left = 0;
		is_working = false;
	}
	int find_worker_id() {
		return worker_id;
	}
	bool find_if_working() {
		return is_working;
	}
	int find_time_left() {
		return time_left;
	}
	void get_car(Car get_car) {
		worker_car = get_car;
		is_working = true;
		worker_car.go_into_progress();
		time_left = worker_time_coefficient * worker_car.find_luxury_coefficient();
	}
	void decrease_time_left() {
		time_left--;
	}
	void car_finished() {
		is_working = false;
		Car c(-1, -1);
		worker_car = c;
	}
	Car find_worker_car() {
		return worker_car;
	}
	int find_car_id() {
		return worker_car.find_car_id();
	}
	int find_luxury_coefficient() {
		return worker_car.find_luxury_coefficient();
	}
	bool is_car_finished() {
		bool ans = false;
		if (worker_car.find_cars_stage() == finished) {
			ans = true;
		}
		return ans;
	}
private:
	int worker_id;
	int  worker_time_coefficient;
	int time_left;
	bool is_working;
	Car worker_car;
};

class Stage {
public:
	Stage(int id, vector<Worker> w) {
		stage_id = id;
		workers = w;
	}
	vector<Car> find_stage_cars() {
		return cars;
	}
	vector<Worker> find_workers() {
		return workers;
	}
	int find_numof_workers() {
		return workers.size();
	}
	void add_car_to_first_stage(Car added_car) {
		cars.push_back(added_car);
	}
	int find_stage_id() {
		return stage_id;
	}
	void replace_cars_and_workers(vector<Car> c, vector<Worker> w) {
		cars = c;
		workers = w;
	}
	void add_car_to_stage(Car car) {
		cars.push_back(car);
	}
private:
	int stage_id;
	vector<Worker> workers;
	vector<Car> cars;
};

class Karvash {
public:
	void show_stage_info(int stage_id) {
		for (int i = 0;i < stages.size();i++) {
			if (stages[i].find_stage_id() == stage_id) {
				print_stage_info_first_part(stages[i]);
				print_stage_info_second_part(stages[i]);
				break;
			}
		}
	}
	void show_carwash_info() {
		cout << "Passed time: " << time << endl;
		cout << "Cars waiting: " << endl;
		for (int i = cars.size() - not_entered_cars;i < cars.size();i++) {
			cout << "Car ID: " << cars[i].find_car_id() << endl;
			cout << "Luxury coefficient: " << cars[i].find_luxury_coefficient() << endl;
		}
		cout << "Stages info: " << endl;
		for (int i = 0;i < stages.size();i++) {
			show_stage_info(i);
		}
		cout << "Cars finished: " << endl;
		for (int i = 0;i < stages.size();i++) {
			vector<Car> cars_of_stage = stages[i].find_stage_cars();
			for (int j = 0;j < cars_of_stage.size();j++) {
				int cars_stage = cars_of_stage[j].find_cars_stage();
				if (!cars_of_stage[j].find_is_in_process() && cars_stage == finished) {
					cout << "Car ID: " << cars_of_stage[j].find_car_id() << endl;
					cout << "Luxury coefficient: " << cars_of_stage[j].find_luxury_coefficient() << endl;
				}
			}
		}
	}
	void add_stage_and_workers(int worker_count,const vector<int>& workers_time_coefficient) {
		vector<Worker> vector_of_workers = add_workers(worker_count, workers_time_coefficient);
		stages.push_back(Stage(stages.size(), vector_of_workers));
	}
	void add_car(int luxury_coefficient) {
		cars.push_back(Car(cars.size(), luxury_coefficient));
		not_entered_cars++;
	}
	void advance_time(int time_steps) {
		for (int t = 0;t < time_steps;t++) {
			time++;
			if (cars.size() > 0) {
				enter_or_leave_with_no_stage_if_not_in_karvash();
				do_process();
			}
		}
	}
	void set_time(int t) {
		time = t;
		not_entered_cars = 0;
	}
	void finish() {
		int finished_cars = count_finished_cars();
		while (finished_cars < cars.size()) {
			finished_cars = count_finished_cars();
			advance_time(1);
		}
		time--;
	}

private:
	int count_finished_cars() {
		int finished_cars = 0;
		for (int i = 0;i < stages.size();i++) {
			vector<Car> cars_of_stage = stages[i].find_stage_cars();
			for (int j = 0;j < cars_of_stage.size();j++) {
				int cars_stage = cars_of_stage[j].find_cars_stage();
				if (!cars_of_stage[j].find_is_in_process() && cars_stage == finished) {
					finished_cars++;
				}
			}
		}
		return finished_cars;
	}
	void do_process() {
		for (int i = 0;i < stages.size();i++) {
			vector<Worker> stage_workers = stages[i].find_workers();
			vector<Car> stage_cars = stages[i].find_stage_cars();
			for (int j = 0;j < stage_workers.size();j++) {
				bool if_working = stage_workers[j].find_if_working();
				bool time_left_finished = stage_workers[j].find_time_left() == 0;

				if (if_working && !time_left_finished) {
					stage_workers[j].decrease_time_left();
				}
				else if (!if_working) {
					start_working(i, stage_workers[j], stage_cars);
				}
				else if (if_working && time_left_finished) {
					release_and_start_working(stage_workers[j], stage_cars);
				}
			}
			stages[i].replace_cars_and_workers(stage_cars, stage_workers);
		}
	}
	void start_working(int stage_id, Worker &stage_workers_j, vector<Car> &stage_cars) {
		for (int k = 0;k < stage_cars.size();k++) {
			int cars_stage_id = stage_cars[k].find_cars_stage();
			if (stage_cars[k].find_is_in_process() == false && cars_stage_id == stage_id) {
				stage_workers_j.get_car(stage_cars[k]);
				stage_cars[k].go_into_progress();
				break;
			}
		}
	}
	void release_and_start_working(Worker &stage_workers_j, vector<Car> &stage_cars) {
		Car released_car = stage_workers_j.find_worker_car();
		int r_stage_id = released_car.find_cars_stage();
		stage_workers_j.car_finished();
		for (int k = 0;k < stage_cars.size();k++) {
			if (stage_cars[k].find_car_id() == released_car.find_car_id()) {
				stage_cars[k].go_to_next_stage(stages.size());
				int sent_stage_id = stage_cars[k].find_cars_stage();
				if (sent_stage_id != finished) {
					stages[sent_stage_id].add_car_to_stage(stage_cars[k]);
				}
				break;
			}
		}
		for (int k = 0;k < stage_cars.size();k++) {
			int k_stage_id = stage_cars[k].find_cars_stage();
			if (stage_cars[k].find_is_in_process() == false && k_stage_id == r_stage_id) {
				stage_workers_j.get_car(stage_cars[k]);
				stage_cars[k].go_into_progress();
				break;
			}
		}
	}
	void enter_or_leave_with_no_stage_if_not_in_karvash() {
		if (not_entered_cars > 0) {
			int cars_size=cars.size();
			Car added_car = cars[cars_size - not_entered_cars];
			added_car.step_with_no_stage(stages.size(), not_entered_cars);
			int cars_stage = added_car.find_cars_stage();
			if (cars_stage == not_in_karvash && cars_stage != finished) {
				not_entered_cars--;
				added_car.go_to_first_stage();
				stages[0].add_car_to_first_stage(added_car);
			}
		}
	}
	void print_cars_waiting(Stage stages_i) {
		int stage_id = stages_i.find_stage_id();
		vector<Car> cars_of_stage = stages_i.find_stage_cars();
		for (int j = 0;j < cars_of_stage.size();j++) {
			int cars_stage = cars_of_stage[j].find_cars_stage();
			if (!cars_of_stage[j].find_is_in_process() && cars_stage == stage_id) {
				cout << "Car ID: " << cars_of_stage[j].find_car_id() << endl;
				cout << "Luxury coefficient: " << cars_of_stage[j].find_luxury_coefficient() << endl;
			}
		}
	}
	void print_stage_info_first_part(Stage stages_i) {
		cout << "Stage ID: " << stages_i.find_stage_id() << endl;
		vector<Worker> workers_of_stage = stages_i.find_workers();
		for (int j = 0;j < workers_of_stage.size();j++) {
			cout << "Worker ID: " << workers_of_stage[j].find_worker_id() << endl;
			if (workers_of_stage[j].find_if_working()) {
				cout << "Car ID: " << workers_of_stage[j].find_car_id() << endl;
				cout << "Luxury coefficient: " << workers_of_stage[j].find_luxury_coefficient() << endl;
				cout << "Time left: " << workers_of_stage[j].find_time_left() << endl;
			}
			else {
				cout << "Free" << endl;
			}
		}
	}
	void print_stage_info_second_part(Stage stages_i) {
		cout << "Cars in waiting queue: " << endl;
		print_cars_waiting(stages_i);
	}
	int find_num_of_workers() {
		int num_of_workers = 0;
		for (int i = 0;i < stages.size();i++) {
			num_of_workers += stages[i].find_numof_workers();
		}
		return num_of_workers;
	}

	vector<Worker> add_workers(int worker_count, vector<int> workers_time_coefficient) {
		vector<Worker> vector_of_workers;
		for (int i = 0;i < worker_count;i++) {
			int num_of_workers = find_num_of_workers();
			int worker_id = num_of_workers + i;
			Car c(-1, -1);//default value
			vector_of_workers.push_back(Worker(worker_id, workers_time_coefficient[i], c));
		}
		return vector_of_workers;
	}
	vector<Car> cars;
	vector<Stage> stages;
	int time;
	int not_entered_cars;
};

vector<int> get_time_coefficient(int worker_count) {
	vector<int> workers_time_coefficient;
	for (int i = 0;i < worker_count;i++) {
		int time_coefficient;
		cin >> time_coefficient;
		workers_time_coefficient.push_back(time_coefficient);
	}
	return workers_time_coefficient;
}

int main() {
	string command;
	Karvash karvash;
	karvash.set_time(zero);
	while (cin >> command) {
		if (command == "add_stage") {
			int worker_count;
			cin >> worker_count;
			vector<int> workers_time_coefficient = get_time_coefficient(worker_count);
			karvash.add_stage_and_workers(worker_count, workers_time_coefficient);
			cout << "OK" << endl;
		}
		else if (command == "add_car") {
			int luxury_coefficient;
			cin >> luxury_coefficient;
			karvash.add_car(luxury_coefficient);
			cout << "OK" << endl;
		}
		else if (command == "advance_time") {
			int time_steps;
			cin >> time_steps;
			karvash.advance_time(time_steps);
			cout << "OK" << endl;
		}
		else if (command == "show_stage_info") {
			int stage_id;
			cin >> stage_id;
			karvash.show_stage_info(stage_id);
		}
		else if (command == "show_carwash_info") {
			karvash.show_carwash_info();
		}
		else if (command == "finish") {
			karvash.finish();
			cout << "OK" << endl;
		}
	}
	return 0;
}