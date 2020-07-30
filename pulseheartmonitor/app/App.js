import React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

import Home from './src/pages/Home'
import Info from './src/pages/Info'
import Profile from './src/pages/Profile'

const Stack = createStackNavigator()

export default function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator initialRouteName="Home">
        <Stack.Screen name="Início" component={Home} />
        <Stack.Screen name="Info" component={Info} />
        <Stack.Screen name="Inserir perfil" component={Profile} />
      </Stack.Navigator>
    </NavigationContainer>
  );
}
