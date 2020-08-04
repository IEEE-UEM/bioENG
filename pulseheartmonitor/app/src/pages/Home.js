import React from 'react';
import {
  ImageBackground,
  StyleSheet,
  Image,
  Text,
  View,
  TouchableOpacity,
} from 'react-native';

function Inicio(props) {

  const pressHandler = () => {
    props.navigation.navigate('Perfil');
  };

  const pressHandler2 = () => {
    props.navigation.navigate('Dados');
  };

  const pressHandler3 = () => {
    //props.navigation.navigate('Sobre');
    console.log('Apertou o Sobre');
  };


  return (
    <ImageBackground style={styles.background}>
      <Image style={styles.logo} source={require('../../assets/logoapp.jpeg')} />
      <TouchableOpacity onPress={pressHandler}>
        <View style={styles.buttonRegister}>
          <Text style={styles.buttonText}>Inserir Perfil</Text>
        </View>
      </TouchableOpacity>
      <TouchableOpacity onPress={pressHandler2}>
        <View style={styles.buttonEnter}>
          <Text style={styles.buttonText}>Dados</Text>
        </View>
      </TouchableOpacity>
      <TouchableOpacity onPress={pressHandler3}>
        <View style={styles.buttonSobre}>
          <Text style={styles.buttonText}>Sobre o Aplicativo</Text>
        </View>
      </TouchableOpacity>
    </ImageBackground>
  );
}

const styles = StyleSheet.create({
  background: {
    backgroundColor: '#332e44',
    flex: 1,
    justifyContent: 'flex-end',
    alignItems: 'center',
  },
  buttonRegister:{
    width: 400,
    alignItems: 'center',
    backgroundColor: '#6959CD',
  },
  buttonEnter: {
    width: 400,
    alignItems: 'center',
    backgroundColor: '#7A67EE',
  },
  buttonText: {
    textAlign: 'center',
    padding: 20,
    color: 'white',
  },
  logo: {
    width: 200,
    height: 200,
    position: 'absolute',
    top: 50,
  },
  buttonSobre: {
    width: 400,
    alignItems: 'center',
    backgroundColor: '#836FFF',
  },
});

export default Inicio;
