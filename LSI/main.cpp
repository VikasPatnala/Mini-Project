#include "./headers/sweepline.h"

int main(int argc, char** argv)
{
    vector<Segment*> data;
    srand(time(NULL));

    if(argc < 1) {
        cout << "Input is wrong\n";
        return -1;
    }

    string a;
    a.assign(argv[1], argv[1] + 1);

    string fname = "./files/test" + a + ".txt";
    ifstream file;
    file.open(fname);

    int n;
    file >> n;

    for (int i = 0; i < n; ++i) {
        double v1, v2, v3, v4;
        file >> v1 >> v2 >> v3 >> v4;
        data.push_back(new Segment(new Point(v1, v2), new Point(v3, v4)));
    }

    int filenum = fname[12] - '0';
    fname = "./files/output" + to_string(filenum) + ".txt";

    Sweepline *test = new Sweepline(data);
    test->FindIntersections();
    test->PrintIntersections();

    ofstream fout;
    fout.open(fname);


    for (int i = 0; i < test->res.size(); ++i) {
        fout << test->res[i]->x << ", " << test->res[i]->y << "\n";
    }
}