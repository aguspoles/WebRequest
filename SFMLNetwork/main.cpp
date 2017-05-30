#include "SFML\Network.hpp"
#include "json.hpp"
#include <iostream>
#include <string>
using namespace std;
using json = nlohmann::json;

int main() {
	sf::Http http;
	http.setHost("http://query.yahooapis.com/");
	sf::Http::Request request;

	cout << "Introduzca nombre de la ciudad sin espacios:";
	string dato;
	cin >> dato;

	sf::Http::Response response;
	try
	{
		request.setUri("/v1/public/yql?q=select%20item.condition.text%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22"
			+ dato + "%2C%20tx%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys");
		response = http.sendRequest(request);
		string s = response.getBody();
		auto j = json::parse(s.begin(), s.end());
		string s1 = j["query"]["results"]["channel"]["item"]["condition"]["text"];
		cout << "Clima:" << s1;
	}
	catch (exception)
	{
		cout << "Nombre incorrecto" << endl;
	}

	fflush(stdin);
	cin.get();
	cin.get();

	return 0;
}