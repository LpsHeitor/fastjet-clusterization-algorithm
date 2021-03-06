#include <stdio.h>
#include <iostream>
#include <fstream>
//#include "dados.h"
#include "tracking.h"

using namespace std;

int main(){
	DataFile data;
	cout << "Rodando codigo: prepareData()" << endl;
	data.prepareData();
	cout << data.getNoHit() << endl;

	cout << "Testando os resultados" << endl;
 	data.prepareResults();
 	// exit(0);

	Tracking teste;
	cout << "Rodando codigo: makeTracking()" << endl;
	teste.makeTracking(data);

	vector<vector<TrackSegment> > trackSegments;
	ofstream trackFile("tracks.txt");
	cout << "Gravando hits" << endl;
	trackSegments = teste.getSimpleSegments();
	for(int i = 0; i < trackSegments.size(); i++){
		for(int j = 0; j < trackSegments[i].size(); j++){
			float x_1000 = trackSegments[i][j].getX_1000();
			float y_1000 = trackSegments[i][j].getY_1000();
			trackFile << x_1000 << " " << y_1000 << endl;
		}
	}
	trackFile.close();
	
	vector<vector<unsigned int> > id_results;
	ofstream real("reais.txt");
	cout << "Gravando informações da simulação" << endl;
	for(int i = 0; i < trackSegments.size(); i++){
		for(int j = 0; j < trackSegments[i].size(); j++){
			for (int k = 0; k < id_results.size(); k++){
				vector<PrPixelHit> simpleSegment = trackSegments[i][j].getTrackSegment();
				unsigned int id1 = simpleSegment[0].id(); 
				unsigned int id2 = simpleSegment[1].id(); //id dos hits do simpleSegment
				unsigned int status_id_1 = find(id_results[k].begin(), id_results[k].end(), id1);
				unsigned int status_id_2 = find(id_results[k].begin(), id_results[k].end(), id2);
				if (status_id_1 != id_results[k].end() && status_id_2 != id_results[k].end()){
					float x_1000 = trackSegments[i][j].getX_1000();
					float y_1000 = trackSegments[i][j].getY_1000();
					real << x_1000 << " " << y_1000 << endl;
				}
			}
		}
	}

//	vector<TrackS> tracks = teste.getTracks();
//	cout << "Rodando codigo: compareTracks(tracks)" << endl;
//	data.compareTracks(tracks);

/*	ofstream trackFile("tracks.txt");
	for(int i = 0; i < tracks.size(); i++){
		vector<PrPixelHit> hits = tracks[i].getHits();
		trackFile << "(";
		for(int j = 0; j < hits.size(); j++){
			trackFile  << hits[j].id() << ", ";
		}
		trackFile << ")" << endl;
	}

	return 0; */
}
