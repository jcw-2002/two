#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// 学生类
class Student {
private:
    string id;
    string name;
public:
    void setID(const string& id) { this->id = id; }
    void setName(const string& name) { this->name = name; }
    void print() const {
        cout << "Student ID: " << id << ", Name: " << name << endl;
    }
    void save(ofstream& outFile) const {
        outFile << "Student ID: " << id << ", Name: " << name << endl;
    }
};

// 轮胎类
class Tire {
private:
    string model;
    int size;
public:
    void setModel(const string& model) { this->model = model; }
    void setSize(int size) { this->size = size; }
    void print() const {
        cout << "Tire Model: " << model << ", Size: " << size << "mm" << endl;
    }
    void save(ofstream& outFile) const {
        outFile << "Tire Model: " << model << ", Size: " << size << "mm" << endl;
    }
};

// 底盘类
class Chassis {
private:
    string id;
    string model;
    int wheelbase;
    int track;
public:
    void setID(const string& id) { this->id = id; }
    void setModel(const string& model) { this->model = model; }
    void setWheelbase(int wheelbase) { this->wheelbase = wheelbase; }
    void setTrack(int track) { this->track = track; }
    void print() const {
        cout << "Chassis ID: " << id << ", Model: " << model
             << ", Wheelbase: " << wheelbase << "mm, Track: " << track << "mm" << endl;
    }
    void save(ofstream& outFile) const {
        outFile << "Chassis ID: " << id << ", Model: " << model
                << ", Wheelbase: " << wheelbase << "mm, Track: " << track << "mm" << endl;
    }
};

// AGX套件类
class AGX {
private:
    string model;
    int cudaCores;
    int tensorCores;
public:
    void setModel(const string& model) { this->model = model; }
    void setCudaCores(int cudaCores) { this->cudaCores = cudaCores; }
    void setTensorCores(int tensorCores) { this->tensorCores = tensorCores; }
    void print() const {
        cout << "AGX Model: " << model << ", CUDA Cores: " << cudaCores
             << ", Tensor Cores: " << tensorCores << endl;
    }
    void save(ofstream& outFile) const {
        outFile << "AGX Model: " << model << ", CUDA Cores: " << cudaCores
                << ", Tensor Cores: " << tensorCores << endl;
    }
};

// 双目摄像头类
class StereoCamera {
private:
    string model;
    string resolution;
public:
    void setModel(const string& model) { this->model = model; }
    void setResolution(const string& resolution) { this->resolution = resolution; }
    void print() const {
        cout << "Stereo Camera Model: " << model << ", Resolution: " << resolution << endl;
    }
    void save(ofstream& outFile) const {
        outFile << "Stereo Camera Model: " << model << ", Resolution: " << resolution << endl;
    }
};

// 激光雷达类
class Lidar {
private:
    string model;
    int range;
public:
    void setModel(const string& model) { this->model = model; }
    void setRange(int range) { this->range = range; }
    void print() const {
        cout << "Lidar Model: " << model << ", Range: " << range << "m" << endl;
    }
    void save(ofstream& outFile) const {
        outFile << "Lidar Model: " << model << ", Range: " << range << "m" << endl;
    }
};

// 电池模块类
class Battery {
private:
    string parameter;
    int capacity;
public:
    void setParameter(const string& parameter) { this->parameter = parameter; }
    void setCapacity(int capacity) { this->capacity = capacity; }
    void print() const {
        cout << "Battery Parameter: " << parameter << ", Capacity: " << capacity << "Ah" << endl;
    }
    void save(ofstream& outFile) const {
        outFile << "Battery Parameter: " << parameter << ", Capacity: " << capacity << "Ah" << endl;
    }
};

// 智能小车类
class SmartCar {
private:
    string id;
    Chassis chassis;
    Tire tires[4];
    AGX agx;
    StereoCamera camera;
    Lidar lidar;
    Battery battery;
    Student assignedStudent;
public:
    void setID(const string& id) { this->id = id; }
    void assignStudent(const Student& student) { assignedStudent = student; }

    void print() const {
        cout << "SmartCar ID: " << id << endl;
        chassis.print();
        for (int i = 0; i < 4; ++i) tires[i].print();
        agx.print();
        camera.print();
        lidar.print();
        battery.print();
        assignedStudent.print();
    }

    void save(ofstream& outFile) const {
        outFile << "SmartCar ID: " << id << endl;
        chassis.save(outFile);
        for (int i = 0; i < 4; ++i) tires[i].save(outFile);
        agx.save(outFile);
        camera.save(outFile);
        lidar.save(outFile);
        battery.save(outFile);
        assignedStudent.save(outFile);
    }
};

// 主程序
int main() {
    vector<SmartCar> cars;
    string filename = "SmartCarData.txt";

    // 创建10辆小车，并为每辆小车分配学生和模块信息
    for (int i = 1; i <= 10; ++i) {
        SmartCar car;
        car.setID("cqusn" + to_string(10000000 + i));

        // 学生信息
        Student student;
        student.setID("202400" + to_string(i));
        student.setName("Student" + to_string(i));
        car.assignStudent(student);

        cars.push_back(car);
    }

    // 保存到文件
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& car : cars) {
            car.save(outFile);
        }
        outFile.close();
    } else {
        cout << "Unable to open file for writing!" << endl;
    }

    // 载入文件并显示
    ifstream inFile(filename);
    if (inFile.is_open()) {
        int index = 0;
        char command;
        while (true) {
            cars[index].print();
            cout << "Enter 'n' for next, 'p' for previous, or 'q' to quit: ";
            cin >> command;

            if (command == 'n') {
                if (index < cars.size() - 1) ++index;
                else cout << "Already at the last car!" << endl;
            } else if (command == 'p') {
                if (index > 0) --index;
                else cout << "Already at the first car!" << endl;
            } else if (command == 'q') {
                break;
            } else {
                cout << "Invalid command!" << endl;
            }
        }
        inFile.close();
    } else {
        cout << "Unable to open file for reading!" << endl;
    }

    return 0;
}
