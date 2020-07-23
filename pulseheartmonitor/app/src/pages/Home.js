import React from 'react';
import { StyleSheet, Text, View, TouchableOpacity } from 'react-native';

export default function Home({ navigation }) {

  function tirarFoto() {
    // Acessar a camera do individuo
    console.log('brandao')
    navigation.navigate('Foto')
  }

  function escolherImagem() {
    // Acessar a galeria do individuo
    console.log('rodolfo')
  }

  return (
    <View style={styles.container}>
      <View>
        <Text>Projeto Pulse Sensor</Text>
      </View>

      <View>
        <TouchableOpacity
          style={styles.button}
          onPress={tirarFoto}
        >
          <Text>Tirar Foto</Text>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles.button}
          onPress={escolherImagem}
        >
          <Text>Escolher imagem na galeria</Text>
        </TouchableOpacity>
      </View>
    </View>
  );
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
    backgroundColor: "#DDDDDD",
    padding: 10
  },
});
