import React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

import Home from './src/pages/Home'
import Photo from './src/pages/Photo'

const Stack = createStackNavigator()

export default function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator initialRouteName="Home">
        <Stack.Screen name="Home" component={Home} />
        <Stack.Screen name="Foto" component={Photo} />
      </Stack.Navigator>
    </NavigationContainer>
  );
}

