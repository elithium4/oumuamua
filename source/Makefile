all: program

program: 	main.o CelestialCoord.o Date.o ObservatoryCartesianFrame.o ObservatoryCylindricalFrame.o Observation.o HubbleInterpolator.o InterpolationTimeFrame.o Converter.o DataHandler.o libsofa.a
			g++ main.o CelestialCoord.o Date.o ObservatoryCartesianFrame.o ObservatoryCylindricalFrame.o Observation.o HubbleInterpolator.o InterpolationTimeFrame.o Converter.o DataHandler.o ../sofa/libsofa_c.a -o ../program

main.o: main.cpp
		g++ -c main.cpp

DataHandler.o: DataHandler.cpp
		g++ -c DataHandler.cpp

Converter.o: Converter.cpp
		g++ -c Converter.cpp

InterpolationTimeFrame.o:
		g++ -c InterpolationTimeFrame.cpp

HubbleInterpolator.o: HubbleInterpolator.cpp
		g++ -c HubbleInterpolator.cpp

ObservatoryCylindricalFrame.o: ObservatoryCylindricalFrame.cpp
		g++ -c ObservatoryCylindricalFrame.cpp

ObservatoryCartesianFrame.o: ObservatoryCartesianFrame.cpp
		g++ -c ObservatoryCartesianFrame.cpp

Observation.o: Observation.cpp
		g++ -c Observation.cpp

Date.o: Date.cpp
		g++ -c Date.cpp

CelestialCoord.o: CelestialCoord.cpp
		g++ -c CelestialCoord.cpp

libsofa.a:
	$(MAKE) -C ../sofa

clean:
	rm -rf *.o program $(&&) 
	$(MAKE) clean -C ../sofa