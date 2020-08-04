import React from 'react'

import { View, Text, TouchableOpacity, StyleSheet, ImageBackground, Image, Dimensions} from 'react-native'

import {
  LineChart,
  BarChart,
  PieChart,
  ProgressChart,
  ContributionGraph
} from 'react-native-chart-kit'

export default function Info({ navigation }) {

    const screenWidth = Dimensions.get('window').width


    const data = {
      labels: ['1', '2', '3', '4', '5', '6','7','8','9','10','11','12'],
      datasets: [{
        data: [ 20, 45, 28, 80, 99, 43, 0, 45, 65, 100, 100,78 ]
      }]
    }

    const chartConfig = {
      backgroundGradientFrom: '#fff',
      backgroundGradientTo: '#fff',
      color: (opacity = 1) => `rgba(0,0,0, ${opacity})`
    }

    const data2 = [0.4 , 0.6, 0.8]

    function alterarPerfil() {
      // Acessar a camera do individuo
      console.log('brandao')
    }

    return (
      <View style={styles.background}>
        <View style={styles.logo}>
          <LineChart
            data={data}
            width={screenWidth}
            height={250}
            chartConfig={{
              backgroundColor: '#332e44',
              backgroundGradientFrom: '#fff',
              backgroundGradientTo: '#fff',
              decimalPlaces: 0, // optional, defaults to 2dp
              color: (opacity = 1) => `rgba(0,0,0, ${opacity})`,
              style: {
                borderRadius: 16
              }
            }}
          />
        </View>
        <View>
          <ProgressChart
            data={data2}
            width={screenWidth}
            height={220}
            chartConfig={chartConfig}
          />
        </View>
        <TouchableOpacity onPress={alterarPerfil}>
          <View style={styles.buttonRegister}>
            <Text style={styles.buttonText}>Modificar Perfil</Text>
          </View>
        </TouchableOpacity>
      </View>
    );
  }

  const styles = StyleSheet.create({
    background: {
      backgroundColor: '#fff',
      flex: 1,
      justifyContent: 'flex-end',
      alignItems: 'center',
    },
    buttonRegister: {
      marginBottom: 20,
      width: 400,
      alignItems: 'center',
      backgroundColor: 'tomato',
    },
    buttonEnter: {
      marginBottom: 20,
      width: 400,
      alignItems: 'center',
      backgroundColor: 'black',
    },
    buttonText: {
      textAlign: 'center',
      padding: 20,
      color: 'white',
    },
    logo: {
      position: 'absolute',
      top: 20,
    },
    buttonSobre: {
      marginBottom: 20,
      width: 400,
      alignItems: 'center',
      backgroundColor: 'tomato',
    },
  });