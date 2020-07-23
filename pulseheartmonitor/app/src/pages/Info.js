import React from 'react'

import { View, Text, TouchableOpacity, StyleSheet } from 'react-native'

export default function Photo({ navigation }) {

    function iniciarScan3D() {
      // Acessar a camera do individuo
      console.log('brandao')
    }

    function escolherImagem() {
      // Acessar a galeria do individuo
      console.log('rodolfo')
      navigation.navigate('Home')
    } 

  return (
    <View>
      <View>
        <TouchableOpacity
          style={styles.button}
          onPress={escolherImagem}
        >
          <Text>Escolher outra imagem</Text>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles.button}
          onPress={iniciarScan3D}
        >
          <Text>Iniciar scan3D</Text>
        </TouchableOpacity>
      </View>
    </View>
  )
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  tinyLogo: {
    width: 50,
    height: 50,
  },
  button: {
    alignItems: "center",
    backgroundColor: "gold",
    padding: 10
  },
});
