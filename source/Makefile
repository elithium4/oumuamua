all: program

program: 	main.o CelestialCoord.o Date.o Velocity.o CartesianFrame.o CylindricalFrame.o GeocentricFrame.o BarycentricFrame.o SphericalFrame.o Observation.o InterpolationHubbleFrame.o ObservatoryData.o InterpolationTimeFrame.o IntegrationVector.o OrbitalIntegration.o Converter.o DataHandler.o LeastSquares.o Facade.o libsofa.a
			g++ main.o CelestialCoord.o Date.o Velocity.o CartesianFrame.o CylindricalFrame.o GeocentricFrame.o BarycentricFrame.o SphericalFrame.o Observation.o InterpolationHubbleFrame.o ObservatoryData.o InterpolationTimeFrame.o IntegrationVector.o OrbitalIntegration.o Converter.o DataHandler.o LeastSquares.o Facade.o ../sofa/libsofa_c.a -o ../program

main.o: main.cpp
		g++ -c main.cpp

Facade.o: Facade.cpp
		g++ -c Facade.cpp

LeastSquares.o: LeastSquares.cpp
		g++ -c LeastSquares.cpp

DataHandler.o: DataHandler.cpp
		g++ -c DataHandler.cpp

Converter.o: Converter.cpp
		g++ -c Converter.cpp

OrbitalIntegration.o: OrbitalIntegration.cpp
		g++ -c OrbitalIntegration.cpp

IntegrationVector.o: IntegrationVector.cpp
		g++ -c IntegrationVector.cpp

InterpolationTimeFrame.o:
		g++ -c InterpolationTimeFrame.cpp

ObservatoryData.o: ObservatoryData.cpp
		g++ -c ObservatoryData.cpp

SphericalFrame.o: SphericalFrame.cpp
		g++ -c SphericalFrame.cpp

BarycentricFrame.o: BarycentricFrame.cpp
		g++ -c BarycentricFrame.cpp

GeocentricFrame.o: GeocentricFrame.cpp
		g++ -c GeocentricFrame.cpp

CylindricalFrame.o: CylindricalFrame.cpp
		g++ -c CylindricalFrame.cpp

CartesianFrame.o: CartesianFrame.cpp
		g++ -c CartesianFrame.cpp

InterpolationHubbleFrame.o: InterpolationHubbleFrame.cpp
		g++ -c InterpolationHubbleFrame.cpp

Observation.o: Observation.cpp
		g++ -c Observation.cpp

Date.o: Date.cpp
		g++ -c Date.cpp

Velocity.o: Velocity.cpp
		g++ -c Velocity.cpp

CelestialCoord.o: CelestialCoord.cpp
		g++ -c CelestialCoord.cpp

libsofa.a:
	$(MAKE) -C ../sofa

clean:
	rm -rf *.o program $(&&) 
	$(MAKE) clean -C ../sofa