import { router } from "expo-router";
import * as SplashScreen from "expo-splash-screen";
import {Pressable, SafeAreaView, StyleSheet, Text, View } from "react-native";
import FontAwesome from "@expo/vector-icons/FontAwesome";
import { useEffect } from "react";
import { useFonts } from "expo-font";
import { Image } from "expo-image";
import { StatusBar } from "expo-status-bar";

SplashScreen.preventAutoHideAsync();

const logoPath = require("../assets/images/logo.png");

export default function index() {

  const [loaded, error] = useFonts({
    "Montserrat-Black": require("../assets/fonts/Montserrat-Black.ttf"),
    "Montserrat-Bold": require("../assets/fonts/Montserrat-Bold.ttf"),
    "Montserrat-ExtraBold": require("../assets/fonts/Montserrat-ExtraBold.ttf"),
    "Montserrat-Light": require("../assets/fonts/Montserrat-Light.ttf"),
    "Montserrat-Medium": require("../assets/fonts/Montserrat-Medium.ttf"),
    "Montserrat-Regular": require("../assets/fonts/Montserrat-Regular.ttf"),
  });

  useEffect(() => {
    if (loaded || error) {
      SplashScreen.hideAsync();
    }
  }, [loaded, error]);

  if (!loaded && !error) {
    return null;
  }


  return (
    <SafeAreaView style={styles.signUp}>
      <StatusBar style="light" backgroundColor="#273443" />
      <Image source={logoPath} style={styles.logo} />


      <Text style={styles.text1}>ESP Remote</Text>

      <Pressable style={styles.view2} 
              onPress={async () => {

                let response = await fetch("http://192.168.8.148?status="+1);

              }}><FontAwesome name="arrow-up" size={60} color={"white"} /></Pressable>

      <View style={styles.view3}>
        <Pressable style={styles.view4}
              onPress={async () => {

                let response = await fetch("http://192.168.8.148?status="+5);

              }}><FontAwesome name="arrow-left" size={60} color={"white"} /></Pressable>
        <Pressable style={styles.view5}
              onPress={async () => {

                let response = await fetch("http://192.168.8.148?status="+3);

              }}><FontAwesome name="stop" size={60} color={"white"} /></Pressable>
        <Pressable style={styles.view6}
              onPress={async () => {

                let response = await fetch("http://192.168.8.148?status="+4);

              }}><FontAwesome name="arrow-right" size={60} color={"white"} /></Pressable>
      </View>

      <Pressable style={styles.view7}
              onPress={async () => {

                let response = await fetch("http://192.168.8.148?status="+2);

              }}><FontAwesome name="arrow-down" size={60} color={"white"} /></Pressable>

      <Pressable style={styles.view8}
               onPress={() => {
                router.push("/home");
              }}><FontAwesome name="map" size={30} color={"white"} /></Pressable>        
    </SafeAreaView>
  );
}



const styles = StyleSheet.create({
  signUp: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: "#273443",
    paddingHorizontal: 25
  },

  logo: {
    height: 140,
    width: 140,
  },

  view: {
    justifyContent: "center",
    alignItems: "center",
    gap: 18,
    padding: 15,
  },

  view2: {
    justifyContent: "center",
    alignItems: "center",
    width: "32%",
    height: 100,
    backgroundColor: "#59ce72",
    borderRadius: 10
  },

  view3: {
    flexDirection: "row",
    width: "100%",
    height: 100,
    columnGap: 10,
    marginVertical: 10
  },

  view4: {
    justifyContent: "center",
    alignItems: "center",
    flex: 1,
    width: 100,
    height: 100,
    backgroundColor: "#59ce72",
    borderRadius: 10
  },

  view5: {
    justifyContent: "center",
    alignItems: "center",
    flex: 1,
    width: 100,
    height: 100,
    backgroundColor: "crimson",
    borderRadius: 10
  },

  view6: {
    justifyContent: "center",
    alignItems: "center",
    flex: 1,
    width: 100,
    height: 100,
    backgroundColor: "#59ce72",
    borderRadius: 10
  },

  view7: {
    justifyContent: "center",
    alignItems: "center",
    width: "32%",
    height: 100,
    backgroundColor: "#59ce72",
    borderRadius: 10,
    marginBottom:32
  },

  view8: {
    justifyContent: "center",
    alignItems: "center",
    width: "60%",
    height: 50,
    backgroundColor: "#ff9428",
    borderRadius: 10
  },

  text1: {
    fontFamily: "Montserrat-Regular",
    fontSize: 18,
    alignSelf: "flex-start",
    color: "#d4d6d8",
    fontWeight: "bold",
    alignSelf: "center",
    marginBottom: 40
  },
});
