module.exports = {
  presets: [
    '@vue/cli-plugin-babel/preset'
  ], 
  // to be able to transcripbe the mqtt javascript code
  // with babel? 
  plugins: [
    "@babel/plugin-transform-private-methods"
  ]
}
