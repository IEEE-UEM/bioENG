import React, { useState } from 'react'
import { View, Text, StyleSheet, TextInput, TouchableOpacity, Alert } from 'react-native'




export default function Profile({navigation}){

    function AddArquivo() {
        console.log('dados')
        Alert.alert('Cadastrado com sucesso!')
        navigation.navigate('Info')
      }
    
   
    //precisamos salvar os valores das caixas quando o botão for pressionado.
  
    
    const [nome, setName] = useState('gabriel')
    const [idade, setAge] = useState('20')
    const [sexo, setGender] = useState('masculino')
    return(
        <View style ={styles.container}>
            <Text> Nome: </Text>
                <TextInput 
                    multiline
                    style={styles.input}
                    placeholder='e.g João da Silva'
                    onChangeText={(val) => setName(val)} />

            <Text> Idade: </Text>
            <TextInput
                style={styles.input}
                placeholder='e.g 20'
                onChangeText={(val) => setAge(val)} />

            <Text> Sexo: </Text>
            <TextInput
                style={styles.input}
                placeholder='e.g Masculino'
                onChangeText={(val) => setGender(val)} />

            <Text>Nome: {nome}, idade: {idade}, Sexo: {sexo}</Text>
        
        
            <TouchableOpacity onPress = {AddArquivo}> 
                <View style={styles.buttonEnviar}>
                    <Text style={styles.buttonText}>Enviar</Text>
                </View>
            </TouchableOpacity>
        </View>
    
  );
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#332e44',
        alignItems:'center',
        justifyContent: 'center',
    },
    input: {
        borderWidth: 5,
        borderColor: '#fff',
        padding: 8,
        margin: 10,
        width: 200,
    },
    buttonEnviar: {
        width: 400,
        alignItems: 'center',
        backgroundColor: '#836FFF',
      },
    buttonText: {
        textAlign: 'center',
        padding: 20,
        color: 'white',
    },
});